#include "benchmark.h"

/* The implementation */
#include "hashtable.h"
#include "rhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define INT_VAL_SIZE sizeof (unsigned)

static Py_uhash_t _Py_hashtable_hash_str (const void * key)
{
  return python_hash (key);
}


static int _Py_hashtable_compare_string (const void * key, const _Py_hashtable_entry_t * entry)
{
  return ! strcmp (entry -> key, key);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "python-udb.c"
#include "python-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
