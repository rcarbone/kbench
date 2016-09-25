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

#include "cwc-udb.c"
#include "cwc-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
