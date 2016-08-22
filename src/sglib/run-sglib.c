#include <stdlib.h>
#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "sglib.h"
#include "rhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* define the initial size of the hash table (0 is illegal) */
#define HASHSIZE  100000

/* define the object of the hash table */
#define OBJ_INT  1
#define OBJ_STR  2
typedef struct obj obj_t;
struct obj
{
  char type;
  unsigned ukey;           /* unsigned key   */
  char skey [16];          /* string key     */
  unsigned val;            /* unsigned value */
  obj_t * self;            /* self pointer   */

  obj_t * _reserved_;      /* field required to make the object hash-able */
};


/* Define a compare function for both integers/string keys */
static int cmp_objs (obj_t * a, obj_t * b)
{
  if (a -> type == OBJ_INT)
    return a -> ukey - b -> ukey;
  else
    return strcmp (a -> skey, b -> skey);
}


/* Define a hash function for both integer/string keys (hash functions are inlined in support.h) */
static uint32_t hash_obj (obj_t * obj)
{
  if (obj -> type == OBJ_INT)
    return java_hash (obj -> ukey);
  else
    return python_hash (obj -> skey);
}

/* Generates typedef and inline functions for the base container (usually a linked list) */
SGLIB_DEFINE_LIST_PROTOTYPES (obj_t, cmp_objs, _reserved_);
SGLIB_DEFINE_LIST_FUNCTIONS (obj_t, cmp_objs, _reserved_);

/* Generates typedef and inline functions for hash table */
SGLIB_DEFINE_HASHED_CONTAINER_PROTOTYPES (obj_t, HASHSIZE, hash_obj);
SGLIB_DEFINE_HASHED_CONTAINER_FUNCTIONS (obj_t, HASHSIZE, hash_obj);

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static  obj_t * objs_unsigned (const unsigned * keys, unsigned n)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  unsigned i;
  for (i = 0; i < n; i ++)
    {
      objs [i] . type = 1;
      objs [i] . ukey = keys [i];
      objs [i] . val = i;
    }
  return objs;
}


static  obj_t * objs_str (char * const * keys, unsigned n)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  unsigned i;
  for (i = 0; i < n; i ++)
    {
      objs [i] . type = 2;
      strcpy (objs [i] . skey, keys [i]);
      objs [i] . val = i;
    }
  return objs;
}


/* Iterate over all the objects to evaluate the hash table size */
static unsigned sglib_hashed_obj_t_size (obj_t * ht [HASHSIZE])
{
  unsigned count = 0;
  obj_t * obj;
  struct sglib_hashed_obj_t_iterator it;

  for (obj = sglib_hashed_obj_t_it_init (& it, ht); obj; obj = sglib_hashed_obj_t_it_next (& it))
    count ++;

  return count;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  obj_t * objs = objs_unsigned (keys, n);
  obj_t ** ht = calloc (HASHSIZE, sizeof (* ht));
  unsigned i;
  unsigned count;

  sglib_hashed_obj_t_init (ht);

  for (i = 0; i < n; i ++)
    {
      obj_t * hit = sglib_hashed_obj_t_find_member (ht, & objs [i]);
      if (hit)
	sglib_hashed_obj_t_delete_if_member (ht, & objs [i], & hit);
      else
	sglib_hashed_obj_t_add (ht, & objs [i]);
    }

  count = sglib_hashed_obj_t_size (ht);

  free (ht);
  free (objs);

  return count;
}


int udb_str (int n, char * const * keys)
{
  obj_t * objs = objs_str (keys, n);
  obj_t ** ht = calloc (HASHSIZE, sizeof (* ht));
  unsigned i;
  unsigned count;

  sglib_hashed_obj_t_init (ht);

  for (i = 0; i < n; i ++)
    {
      obj_t * hit = sglib_hashed_obj_t_find_member (ht, & objs [i]);
      if (hit)
	sglib_hashed_obj_t_delete_if_member (ht, & objs [i], & hit);
      else
	sglib_hashed_obj_t_add (ht, & objs [i]);
    }

  count = sglib_hashed_obj_t_size (ht);

  free (ht);
  free (objs);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
