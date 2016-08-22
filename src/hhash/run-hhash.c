#include "benchmark.h"

/* The implementation */
#include "hhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned hhashcount (HHash * ht)
{
  return ht -> m;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  /* Warning: 0 cannot be used as value */
  HHash * ht = hhashnew (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hhashget (ht, keys [i], 0))
	hhashdel (ht, keys [i], 0);
      else
	hhashput (ht, keys [i], keys [i]);
    }

  count = hhashcount (ht);

  hhashfree (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  return 0;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
