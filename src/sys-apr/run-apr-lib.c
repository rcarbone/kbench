#include <stdio.h>

#include "benchmark.h"

/* The implementation */
#define __USE_LARGEFILE64
#include <apr-1.0/apr_hash.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define apr_hash_del(x, y, z)  apr_hash_set(x, y, z, NULL)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  apr_pool_t * p;
  apr_hash_t * ht;
  unsigned i;
  unsigned count;

  apr_pool_initialize ();
  apr_pool_create (& p, NULL);

  ht = apr_hash_make (p);

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, & keys [i], sizeof (keys [i])))
	apr_hash_del (ht, & keys [i], sizeof (keys [i]));
      else
	apr_hash_set (ht, & keys [i], sizeof (keys [i]), & keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_clear (ht);
  apr_pool_destroy (p);
  apr_pool_terminate ();

  return count;
}


int udb_str (int n, char * const * keys)
{
  apr_pool_t * p;
  apr_hash_t * ht;
  unsigned i;
  unsigned count;

  apr_pool_initialize ();
  apr_pool_create (& p, NULL);

  ht = apr_hash_make (p);

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, keys [i], strlen (keys [i])))
	apr_hash_del (ht, keys [i], strlen (keys [i]));
      else
	apr_hash_set (ht, keys [i], strlen (keys [i]), keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_clear (ht);
  apr_pool_destroy (p);
  apr_pool_terminate ();

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
