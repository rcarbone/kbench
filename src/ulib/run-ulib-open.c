#include "benchmark.h"

/* The implementation */
#include "hash_open_prot.h"
#include "rhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define OPENHASH_ISMAP  1
#define OPENHASH_ISSET  0

/* identity hash function to convert an integer key to an integer */
static int hash_int_fn (unsigned key)
{
  return openhash_hashfn (key);
}


/* boolean function that tests whether two keys are equal */
static int eq_int_fn (unsigned k1, unsigned k2)
{
  return openhash_equalfn (k1, k2);
}


static int hash_str_fn (char * key)
{
  return python_hash (key);
}


static int eq_str_fn (char * k1, char * k2)
{
  return ! strcmp (k1, k2);
}


/* Generates typedef for hash table and inline functions */
DEFINE_OPENHASH (uht_t, unsigned, unsigned, OPENHASH_ISMAP, hash_int_fn, eq_int_fn)
DEFINE_OPENHASH (sht_t, char *, unsigned, OPENHASH_ISMAP, hash_str_fn, eq_str_fn)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#include "ulib-open-udb.c"
#include "ulib-open-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
