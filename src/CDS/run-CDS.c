#include "benchmark.h"

/* The implementation */
#include "hash_map.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned HashDjb2 (char * key)
{
  unsigned hash = 5381;
  int c;

  while ((c = * key ++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}


static unsigned HashKey (void * key)
{
  return HashDjb2 ((char *) key);
}


static int CompareKey (void * lhs, void * rhs)
{
  return strcmp ((char *) lhs, (char *) rhs);
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  HashMap * ht = HashMapInit ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (HashMapGet (ht, (void *) (intptr_t) keys [i]))
	HashMapRemove (ht, (void *) (intptr_t) keys [i]);
      else
	HashMapPut (ht, (void *) (intptr_t) keys [i], (void *) (intptr_t) keys [i]);
    }

  count = HashMapSize (ht);

  HashMapDeinit (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  HashMap * ht = HashMapInit ();
  unsigned i;
  unsigned count;

  /* Set the custom hash value generator and key comparison functions */
  HashMapSetHash (ht, HashKey);
  HashMapSetCompare (ht, CompareKey);

  for (i = 0; i < n; i ++)
    {
      if (HashMapGet (ht, keys [i]))
	HashMapRemove (ht, keys [i]);
      else
	HashMapPut (ht, keys [i], & i);
    }

  count = HashMapSize (ht);

  HashMapDeinit (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
