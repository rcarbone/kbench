#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "hashtable.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "rhash.h"

static unsigned hash_int_key_fn (void * key)
{
  return java_hash (* (unsigned *) key);
}


static unsigned hash_str_key_fn (void * key)
{
  return python_hash (key);
}


static int eq_int_key_fn (void * key1, void * key2)
{
  return * (unsigned *) key1 == * (unsigned *) key2;
}


static int eq_str_key_fn (void * key1, void * key2)
{
  return ! strcmp (key1, key2);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  struct hashtable * ht = create_hashtable (0, hash_int_key_fn, eq_int_key_fn);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hashtable_search (ht, & keys [i]))
	hashtable_remove (ht, & keys [i]);
      else
	hashtable_insert (ht, & keys [i], & i);
    }

  count = hashtable_count (ht);

  hashtable_destroy (ht, 0);

  return count;
}


int udb_str (int n, char * const * keys)
{
  struct hashtable * ht = create_hashtable (0, hash_str_key_fn, eq_str_key_fn);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hashtable_search (ht, keys [i]))
	hashtable_remove (ht, keys [i]);
      else
	hashtable_insert (ht, keys [i], & i);
    }

  count = hashtable_count (ht);

  hashtable_destroy (ht, 0);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
