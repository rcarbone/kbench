#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "tommyhashdyn.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "objs.c"

static tommy_hashdyn * tommy_hashdyn_alloc (void)
{
  tommy_hashdyn * ht = calloc (1, sizeof (* ht));
  tommy_hashdyn_init (ht);
  return ht;
}


static void tommy_hashdyn_free (tommy_hashdyn * ht)
{
  tommy_hashdyn_done (ht);
  free (ht);
}


/* The callback comparison function to look up for matching values */
static int cmp_int (const void * val, const void * obj)
{
  return * (unsigned *) val - ((obj_t *) obj) -> uval;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  obj_t ** objs = setup_int_objs (n, keys);
  tommy_hashdyn * ht = tommy_hashdyn_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (tommy_hashdyn_search (ht, cmp_int, & objs [i] -> uval, objs [i] -> uhash))
	tommy_hashdyn_remove (ht, cmp_int, & objs [i] -> uval, objs [i] -> uhash);
      else
	tommy_hashdyn_insert (ht, & objs [i] -> _reserved_, objs [i], objs [i] -> uhash);
    }

  count = tommy_hashdyn_count (ht);

  tommy_hashdyn_free (ht);
  teardown (n, objs);

  return count;
}


int udb_str (int n, char * const * keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashdyn * ht = tommy_hashdyn_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (tommy_hashdyn_search (ht, cmp_int, & objs [i] -> uval, objs [i] -> uhash))
	tommy_hashdyn_remove (ht, cmp_int, & objs [i] -> uval, objs [i] -> uhash);
      else
	tommy_hashdyn_insert (ht, & objs [i] -> _reserved_, & objs [i] -> uval, objs [i] -> uhash);
    }

  count = tommy_hashdyn_count (ht);

  tommy_hashdyn_free (ht);
  teardown (n, objs);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
