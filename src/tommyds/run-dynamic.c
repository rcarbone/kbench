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

#include "tommyds-dynamic-udb.c"
#include "tommyds-dynamic-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
