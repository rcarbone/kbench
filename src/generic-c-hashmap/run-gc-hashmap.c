#include <stdlib.h>

#include "benchmark.h"

/* The implementation */
#include "hashmap.h"
#include "rhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Object definition */
typedef struct obj obj_t;
struct obj
{
  unsigned ukey;
  char skey [32];
  unsigned uval;
};


static int cmp_int_fn (obj_t * obj1, obj_t * obj2)
{
  return obj1 -> ukey - obj2 -> ukey;
}


static int hash_int_fn (obj_t * obj)
{
  return java_hash (obj -> ukey);
}


static int cmp_str_fn (obj_t * obj1, obj_t * obj2)
{
  return strcmp (obj1 -> skey, obj2 -> skey);
}


static int hash_str_fn (obj_t * obj)
{
  return python_hash (obj -> skey);
}


/* Generates typedef for hash table and inline functions */
DEFINE_HASHMAP(gch_int_, obj_t)
DECLARE_HASHMAP(gch_int_, cmp_int_fn, hash_int_fn, free, realloc)
typedef gch_int_ gch_int_t;

DEFINE_HASHMAP(gch_str_, obj_t)
DECLARE_HASHMAP(gch_str_, cmp_str_fn, hash_str_fn, free, realloc)
typedef gch_str_ gch_str_t;


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "gc-udb.c"
#include "gc-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
