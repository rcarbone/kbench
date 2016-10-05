#include <stdio.h>
#include <string.h>

#include "benchmark.h"
#include "rhash.h"

/* The implementation */
#include "dict.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned int_hash_f (const void * keyp)
{
  unsigned long key = (unsigned long) keyp;
  key = dictGenHashFunction (& key, sizeof (key));
  key += ~(key << 15);
  key ^=  (key >> 10);
  key +=  (key << 3);
  key ^=  (key >> 6);
  key += ~(key << 11);
  key ^=  (key >> 16);
  return key;
}


static int int_cmp_f (void * privdata, const void * key1, const void * key2)
{
  unsigned long k1 = (unsigned long) key1;
  unsigned long k2 = (unsigned long) key2;
  return k1 == k2;
}


static unsigned str_hash_f (const void * keyp)
{
  return python_hash (keyp);
}


static int str_cmp_f (void * privdata, const void * key1, const void * key2)
{
  return ! strcmp (key1, key2);
}


static dictType int_dict =
{
  int_hash_f,                    /* hash function */
  NULL,                          /* key dup */
  NULL,                          /* val dup */
  int_cmp_f,                     /* key compare */
  NULL,                          /* key destructor */
  NULL                           /* val destructor */
};


static dictType str_dict =
{
  str_hash_f,                    /* hash function */
  NULL,                          /* key dup */
  NULL,                          /* val dup */
  str_cmp_f,                     /* key compare */
  NULL,                          /* key destructor */
  NULL                           /* val destructor */
};

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "udb.c"
#include "grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, NULL, NULL);
}
