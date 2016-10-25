#include <string.h>

#include "benchmark.h"
#include "rhash.h"

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
  return strcmp (((obj_t *) key) -> skey, ((obj_t *) obj) -> skey);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "tommyds-linear-udb.c"
#include "tommyds-linear-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
