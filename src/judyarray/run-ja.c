#include "benchmark.h"

/* The implementation */
#include "judyarray.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define KEYSIZE sizeof (unsigned)
#define VALSIZE 1

#define judy_add  judy_cell
#define judy_find judy_slot


static unsigned judy_count (Judy * ht)
{
  unsigned count = 0;
#if defined(ROCCO)
  unsigned key = 0;
  JudySlot * ji = judy_strt (ht, (uchar *) & key, 0);
#else
  JudySlot * ji = judy_strt (ht, NULL, 0);
#endif /* ROCCO */
  while (ji)
    {
      count ++;
      ji = judy_nxt (ht);
    }
  return count;
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  Judy * ht = judy_open (KEYSIZE, VALSIZE);
  unsigned i;
  unsigned count = 0;

#if !defined(ROCCO)
  for (i = 0; i < n; i ++)
    {
      JudySlot * hit = judy_find (ht, (uchar *) & keys [i], sizeof (unsigned));
      if (hit)
	{
	  judy_del (ht);
	  count --;
	}
      else
	{
	  unsigned * val = (unsigned *) judy_add (ht, (uchar *) & keys [i], sizeof (unsigned));
	  if (val)
	    * val = i + 1;
	  count ++;
	}
    }
#else

  for (i = 0; i < n; i ++)
    {
      unsigned * val = (unsigned *) judy_add (ht, (uchar *) keys [i], KEYSIZE);
      if (val)
	* val = i + 1;
      count ++;
    }

#endif /* ROCCO */

  printf ("IO %u\n", count);
  count = judy_count (ht);
  printf ("JC %u\n", count);

  judy_close (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  Judy * ht = judy_open (KEYSIZE, 0);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
#if defined(ROCCO)
      JudySlot * hit = judy_find (ht, (uchar *) keys [i], 0);
      if (hit)
	judy_del (ht);
      else
#endif /* ROCCO */
	* (unsigned *) judy_add (ht, (uchar *) keys [i], 0) = i;
    }

  count = judy_count (ht);

  judy_close (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
