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

int udb_int (int n, const unsigned * keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  ht_int_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      objs [i] . ukey = keys [i];
      objs [i] . uval = i;
    }

  HT_INIT (evht_int, ht);

  for (i = 0; i < n; i ++)
    {
      obj_t * hit = HT_FIND (evht_int, ht, & objs [i]);
      if (hit)
	HT_REMOVE (evht_int, ht, hit);
      else
	HT_INSERT (evht_int, ht, & objs [i]);
    }

  count = HT_SIZE (ht);

  HT_CLEAR (evht_int, ht);
  free (ht);
  free (objs);

  return count;
}


int udb_str (int n, char * const * keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  ht_str_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      strcpy (objs [i] . skey, keys [i]);
      objs [i] . uval = i;
    }

  for (i = 0; i < n; i ++)
    {
      obj_t * hit = HT_FIND (evht_str, ht, & objs [i]);
      if (hit)
	HT_REMOVE (evht_str, ht, hit);
      else
	HT_INSERT (evht_str, ht, & objs [i]);
    }

  count = HT_SIZE (ht);

  HT_CLEAR (evht_str, ht);
  free (ht);
  free (objs);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
