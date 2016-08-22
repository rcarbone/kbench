#include "benchmark.h"

/* The implementation */
#include "apr_hash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define apr_hash_del(x, y, z)  apr_hash_set(x, y, z, NULL)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  apr_hash_t * ht = apr_hash_make (NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, & keys [i], sizeof (keys [i])))
	apr_hash_del (ht, & keys [i], sizeof (keys [i]));
      else
	apr_hash_set (ht, & keys [i], sizeof (keys [i]), & keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_done (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  apr_hash_t * ht = apr_hash_make (NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, keys [i], strlen (keys [i])))
	apr_hash_del (ht, keys [i], strlen (keys [i]));
      else
	apr_hash_set (ht, keys [i], strlen (keys [i]), keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_done (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
