#include "benchmark.h"

/* The implementation */
#include "hash-table.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "hash-int.h"
#include "compare-int.h"
#include "hash-string.h"
#include "compare-string.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  HashTable * ht = hash_table_new (int_hash, int_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hash_table_lookup (ht, (unsigned *) & keys [i]))
	hash_table_remove (ht, (unsigned *) & keys [i]);
      else
	hash_table_insert (ht, (unsigned *) & keys [i], & i);
    }

  count = hash_table_num_entries (ht);

  hash_table_free (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  HashTable * ht = hash_table_new (string_hash, string_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hash_table_lookup (ht, keys [i]))
	hash_table_remove (ht, keys [i]);
      else
	hash_table_insert (ht, keys [i], & i);
    }

  count = hash_table_num_entries (ht);

  hash_table_free (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
