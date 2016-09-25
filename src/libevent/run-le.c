#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "ht-internal.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Object definition */
typedef struct obj obj_t;
struct obj
{
  unsigned ukey;
  char skey [32];
  unsigned uval;

  HT_ENTRY(obj) _reserved_;   /* field required to make the object hash-able */
};


/* Hash table naming and definition */
HT_HEAD(evht_int, obj);
typedef struct evht_int ht_int_t;

HT_HEAD(evht_str, obj);
typedef struct evht_str ht_str_t;


/* Forward */
static unsigned int_hash_f (obj_t * obj);
static int int_cmp_f (obj_t * a, obj_t * b);

static unsigned str_hash_f (obj_t * obj);
static int str_cmp_f (obj_t * a, obj_t * b);


/* Generates prototypes and inline functions */
HT_PROTOTYPE (evht_int, obj, _reserved_, int_hash_f, int_cmp_f)
HT_GENERATE (evht_int, obj, _reserved_, int_hash_f, int_cmp_f, 0.5, malloc, realloc, free)

HT_PROTOTYPE (evht_str, obj, _reserved_, str_hash_f, str_cmp_f)
HT_GENERATE (evht_str, obj, _reserved_, str_hash_f, str_cmp_f, 0.5, malloc, realloc, free)


/* Hash for unsigned keys */
static unsigned int_hash_f (obj_t * obj)
{
  return ht_improve_hash_ (obj -> ukey);    /* internal defined helper function for basic integer hashing (Java) */
}


/* Compare 2 objects for unsigned keys equality */
static int int_cmp_f (obj_t * a, obj_t * b)
{
  return a -> ukey == b -> ukey;
}


/* Hash for string keys */
static unsigned str_hash_f (obj_t * obj)
{
  return ht_string_hash_ (obj -> skey);    /* internal defined helper function for basic string hashing (Python) */
}


/* Compare 2 objects for string keys equality */
static int str_cmp_f (obj_t * a, obj_t * b)
{
  return ! strcmp (a -> skey, b -> skey);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "libevent-udb.c"
#include "libevent-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
