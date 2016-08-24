#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "tommyhashlin.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "objs.c"

static tommy_hashlin * tommy_hashlin_alloc (void)
{
  tommy_hashlin * ht = calloc (1, sizeof (* ht));
  tommy_hashlin_init (ht);
  return ht;
}


static void tommy_hashlin_free (tommy_hashlin * ht)
{
  tommy_hashlin_done (ht);
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
  tommy_hashlin * ht = tommy_hashlin_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (tommy_hashlin_search (ht, cmp_int, objs [i], tommy_inthash_u64 (objs [i] -> ukey)))
	tommy_hashlin_remove (ht, cmp_int, objs [i], tommy_inthash_u64 (objs [i] -> ukey));
      else
	tommy_hashlin_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_inthash_u64 (objs [i] -> ukey));
    }

  count = tommy_hashlin_count (ht);

  tommy_hashlin_free (ht);
  teardown (n, objs);

  return count;
}


int udb_str (int n, char * const * keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashlin * ht = tommy_hashlin_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (tommy_hashlin_search (ht, cmp_str, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey))))
	tommy_hashlin_remove (ht, cmp_str, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey)));
      else
	tommy_hashlin_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey)));
    }

  count = tommy_hashlin_count (ht);

  tommy_hashlin_free (ht);
  teardown (n, objs);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
