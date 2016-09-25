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

#include "tommyds-fixed-udb.c"
#include "tommyds-fixed-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
