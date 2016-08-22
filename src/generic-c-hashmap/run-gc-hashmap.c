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

int udb_int (int n, const unsigned * keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  gch_int_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      objs [i] . ukey = keys [i];
      objs [i] . uval = i;
    }

  for (i = 0; i < n; i ++)
    {
      obj_t * obj = & objs [i];
      if (gch_int_Find (ht, & obj))
	gch_int_Remove (ht, obj);
      else
	gch_int_Put (ht, & obj, HMDR_STACK);
    }

  count = ht -> size;

  gch_int_Destroy (ht);
  free (ht);
  free (objs);

  return count;
}


int udb_str (int n, char * const * keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  gch_str_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      strcpy (objs [i] . skey, keys [i]);
      objs [i] . uval = i;
    }

  for (i = 0; i < n; i ++)
    {
      obj_t * obj = & objs [i];
      if (gch_str_Find (ht, & obj))
	gch_str_Remove (ht, obj);
      else
	gch_str_Put (ht, & obj, HMDR_STACK);
    }

  count = ht -> size;

  gch_str_Destroy (ht);
  free (ht);
  free (objs);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
