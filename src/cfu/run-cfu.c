#include "benchmark.h"

/* The implementation */
#include "cfuhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  cfuhash_table_t * ht = cfuhash_new ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (cfuhash_exists_data (ht, & keys [i], sizeof (keys [i])))
	cfuhash_delete_data (ht, & keys [i], sizeof (keys [i]));
      else
	cfuhash_put_data (ht, & keys [i], sizeof (keys [i]), & i, sizeof (i), NULL);
    }

  count = cfuhash_num_entries (ht);

  cfuhash_destroy (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  cfuhash_table_t * ht = cfuhash_new ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (cfuhash_exists (ht, keys [i]))
	cfuhash_delete (ht, keys [i]);
      else
	cfuhash_put (ht, keys [i], & i);
    }

  count = cfuhash_num_entries (ht);

  cfuhash_destroy (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
