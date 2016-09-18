#include <stdio.h>

#include "benchmark.h"

/* The implementation */
#include <Judy.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  Pvoid_t ht = NULL;
  unsigned i;
  Word_t r;
  Word_t count;

  for (i = 0; i < n; i ++)
    {
      Word_t * p;
      JLG (p, ht, keys [i]);
      if (p)
	{
	  JLD (r, ht, keys [i]);
	}
      else
	{
	  JLI (p, ht, keys [i]);
	  * p = i;
	}
    }

  JLC (count, ht, 0, -1);

  JLFA (r, ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  Pvoid_t ht = NULL;
  unsigned i;
  Word_t r;
  Word_t count;

  for (i = 0; i < n; i ++)
    {
      Word_t * p;
      JSLG (p, ht, (char *) keys [i]);
      if (p)
	{
	  JSLD (r, ht, keys [i]);
	}
      else
	{
	  JSLI (p, ht, keys [i]);
	  * p = i;
	}
    }

  JLC (count, ht, 0, -1);

  JSLFA (r, ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
