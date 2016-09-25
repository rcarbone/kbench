#include <stdio.h>
#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "hashtab.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "rhash.h"

static hashval_t hash_int_fn (const void * key)
{
  return java_hash (* (unsigned *) key);
}


static int eq_int_fn (const void * key1, const void * key2)
{
  return * (unsigned *) key1 == * (unsigned *) key2;
}


static hashval_t hash_str_fn (const void * key)
{
  return python_hash (key);
}


static int eq_str_fn (const void * key1, const void * key2)
{
  return ! strcmp (key1, key2);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "gcc-udb.c"
#include "gcc-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
