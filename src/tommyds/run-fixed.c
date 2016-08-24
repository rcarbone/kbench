#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "tommyhashtbl.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "objs.c"

static tommy_hashtable * tommy_hashtable_alloc (unsigned n)
{
  tommy_hashtable * ht = calloc (1, sizeof (* ht));
  tommy_hashtable_init (ht, n);
  return ht;
}


static void tommy_hashtable_free (tommy_hashtable * ht)
{
  tommy_hashtable_done (ht);
  free (ht);
}


/* The callback comparison function to look up for matching keys */
static int cmp_int (const void * key, const void * obj)
{
  return * (unsigned *) key == ((obj_t *) obj) -> ukey;
}


/* The callback comparison function to look up for matching keys */
static int cmp_str (const void * key, const void * obj)
{
  return ! strcmp (key, ((obj_t *) obj) -> skey);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  obj_t ** objs = setup_int_objs (n, keys);
  tommy_hashtable * ht = tommy_hashtable_alloc (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (tommy_hashtable_search (ht, cmp_int, objs [i], tommy_inthash_u64 (objs [i] -> ukey)))
	tommy_hashtable_remove (ht, cmp_int, objs [i], tommy_inthash_u64 (objs [i] -> ukey));
      else
	tommy_hashtable_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_inthash_u64 (objs [i] -> ukey));
    }

  count = tommy_hashtable_count (ht);

  tommy_hashtable_free (ht);
  teardown (n, objs);

  return count;
}


int udb_str (int n, char * const * keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashtable * ht = tommy_hashtable_alloc (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (tommy_hashtable_search (ht, cmp_str, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey))))
	tommy_hashtable_remove (ht, cmp_str, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey)));
      else
	tommy_hashtable_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey)));
    }

  count = tommy_hashtable_count (ht);

  tommy_hashtable_free (ht);
  teardown (n, objs);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
