#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "htable.h"
#include "hash.h"


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Hash is simply key itself */
static size_t hash_int_fn (const void * key, void * unused)
{
  return * (unsigned *) key;
}


static bool eq_int_fn (const void * a, void * b)
{
  return * (unsigned *) a == * (unsigned *) b;
}


static size_t hash_str_fn (const void * key, void * unused)
{
  return hash_string (key);
}


static bool eq_str_fn (const void * a, void * b)
{
  return ! strcmp (a, b);
}


static unsigned htable_count (struct htable * ht)
{
  return ht -> elems;
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "ccan-udb.c"
#include "ccan-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
