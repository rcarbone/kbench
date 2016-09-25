#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include "runlib.h"
#define UDB_SEED 11


static int data_size       = 5e6;     /* 5 million elements */
static unsigned * int_data = NULL;
static char ** str_data    = NULL;


static void udb_destroy_data (unsigned n)
{
  unsigned i;

  for (i = 0; i < n; i ++)
    free (str_data [i]);

  free (str_data);
  free (int_data);
}


static void udb_timing_int (unsigned (* func) (unsigned, unsigned *))
{
  pid_t pid = getpid ();
  RunProcDyn rpd0, rpd1;
  double ut, st;
  unsigned ret;

  if (! func)
    return;

  run_get_dynamic_proc_info (pid, & rpd0);
  ret = func (data_size, int_data);
  run_get_dynamic_proc_info (pid, & rpd1);

  printf ("[int data] # elements: %u\n", ret);

  ut = rpd1 . utime - rpd0 . utime;
  st = rpd1 . stime - rpd0 . stime;

  printf ("[int data] CPU time: %.3lf (= %.3lf + %.3lf)\n", ut + st, ut, st);
}


static void udb_timing_str (unsigned (* func) (unsigned, char **))
{
  pid_t pid = getpid ();
  RunProcDyn rpd0, rpd1;
  double ut, st;
  unsigned ret;

  if (! func)
    return;

  run_get_dynamic_proc_info (pid, & rpd0);
  ret = func (data_size, str_data);
  run_get_dynamic_proc_info (pid, & rpd1);

  printf ("[str data] # elements: %u\n", ret);

  ut = rpd1 . utime - rpd0 . utime;
  st = rpd1 . stime - rpd0 . stime;

  printf ("[str data] CPU time: %.3lf (= %.3lf + %.3lf)\n", ut + st, ut, st);
}


/* UDB dataset */
void udb_init_data (unsigned n)
{
  unsigned i;
  char buf [256];

  printf ("[benchmark] generating data... [UDB] ");

  srand48 (UDB_SEED);

  int_data = calloc (n, sizeof (unsigned));
  str_data = calloc (n, sizeof (char *));

  for (i = 0; i < n; i ++)
    {
      int_data [i] = (unsigned) (n * drand48 () / 4) * 271828183u;
      sprintf (buf, "%x", int_data [i]);
      str_data [i] = strdup (buf);
    }

  printf ("done!\n");
}


/* Linear grow dataset */
void grow_init_data (unsigned n)
{
  unsigned i;
  char buf [256];

  printf ("[benchmark] generating data... [linear] ");

  int_data = calloc (n, sizeof (unsigned));
  str_data = calloc (n, sizeof (char *));

  for (i = 0; i < n; i ++)
    {
      int_data [i] = i;
      sprintf (buf, "%x", int_data [i]);
      str_data [i] = strdup (buf);
    }

  printf ("done!\n");
}




int udb_benchmark (int argc, char * argv [],
		   unsigned (* udb_int) (unsigned, unsigned *),
		   unsigned (* udb_str) (unsigned, char **),
		   unsigned (* grow_int) (unsigned, unsigned *),
		   unsigned (* grow_str) (unsigned, char **)
		   )
{
  pid_t pid = getpid ();
  int flag = 0;
  void (* init_data) (unsigned n) = udb_init_data;
  int dataset = 1;
  int c;
  size_t init_rss;
  RunProcDyn rpd;

  while ((c = getopt (argc, argv, "isn:12")) != -1)
    {
      switch (c)
	{
	case 'i': flag |= 1; break;
	case 's': flag |= 2; break;
	case 'n': data_size = atoi (optarg); break;
	case '1': init_data = udb_init_data; break;
	case '2': init_data = grow_init_data; break;
	}
    }

  if (flag == 0)
    {
      printf ("Usage: %s [-is] [-n %d] [-12]\n", argv [0], data_size);
      return 1;
    }

  /* Initialize dataset */
  init_data (data_size);

  run_get_dynamic_proc_info (pid, & rpd);

  init_rss = rpd . rss;

  printf ("[benchmark] initial rss: %.3lf kB\n", rpd . rss / 1024.0);

  if (flag & 1)
    {
      switch (dataset)
	{
	case 1: udb_timing_int (udb_int);  break;
	case 2: udb_timing_int (grow_int); break;
	}
    }

  if (flag & 2)
    {
      switch (dataset)
	{
	case 1: udb_timing_str (udb_str);  break;
	case 2: udb_timing_str (grow_str); break;
	}
    }

  run_get_dynamic_proc_info (pid, & rpd);

  printf ("[benchmark] rss diff: %.3lf kB\n", (rpd . rss - init_rss) / 1024.0);

  udb_destroy_data (data_size);

  printf ("[benchmark] finished!\n");

  return 0;
}
