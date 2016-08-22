#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "hashit.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define H_HT_TYPE  CHAIN_H

static int cmp_int_fn (void * a, void * b)
{
  return * (unsigned *) a - * (unsigned *) b;
}


static int cmp_str_fn (void * a, void * b)
{
  return strcmp (a, b);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  hash_t ht = hashit_create (n, sizeof (unsigned), NULL, cmp_int_fn, H_HT_TYPE);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hashit_lookup (ht, (unsigned *) & keys [i]))
	hashit_delete (ht, (unsigned *) & keys [i]);
      else
	hashit_insert (ht, (unsigned *) & keys [i], & i);
    }

  count = hashit_size (ht);

  hashit_destroy (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  hash_t ht = hashit_create (n, 0, NULL, cmp_str_fn, H_HT_TYPE);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hashit_lookup (ht, keys [i]))
	hashit_delete (ht, keys [i]);
      else
	hashit_insert (ht, keys [i], & i);
    }

  count = hashit_size (ht);

  hashit_destroy (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
