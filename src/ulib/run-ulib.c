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
DEFINE_OPENHASH (try_int, unsigned, unsigned, OPENHASH_ISMAP, hash_int_fn, eq_int_fn)
DEFINE_OPENHASH (try_str, char *, unsigned, OPENHASH_ISMAP, hash_str_fn, eq_str_fn)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  openhash_t(try_int) * ht = openhash_init (try_int);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      oh_iter_t hi = openhash_get (try_int, ht, keys [i]);
      if (hi != openhash_end (ht))
	openhash_del (try_int, ht, hi);
      else
	{
	  int ret;
	  hi = openhash_set (try_int, ht, keys [i], & ret);
	  openhash_value (ht, hi) = keys [i];
	}
    }

  count = openhash_size (ht);

  openhash_destroy (try_int, ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  openhash_t(try_str) * ht = openhash_init (try_str);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      oh_iter_t hi = openhash_get (try_str, ht, keys [i]);
      if (hi != openhash_end (ht))
	openhash_del (try_str, ht, hi);
      else
	{
	  int ret;
	  hi = openhash_set (try_str, ht, keys [i], & ret);
	  openhash_value (ht, hi) = i;
	}
    }

  count = openhash_size (ht);

  openhash_destroy (try_str, ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
