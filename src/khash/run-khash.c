#include "benchmark.h"

/* The implementation */
#include "khash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Instantiate structs and methods */
KHASH_MAP_INIT_INT(uht, unsigned)
KHASH_MAP_INIT_STR(sht, unsigned)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  khash_t(uht) * ht = kh_init (uht);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      khiter_t hit = kh_get (uht, ht, keys [i]);
      if (hit != kh_end (ht))
	kh_del (uht, ht, hit);
      else
	{
	  int ret;
	  kh_put (uht, ht, keys [i], & ret);
	  kh_value (ht, hit) = i;
	}
    }

  count = kh_size (ht);

  kh_destroy (uht, ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  khash_t(sht) * ht = kh_init (sht);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      khiter_t hit = kh_get (sht, ht, keys [i]);
      if (hit != kh_end (ht))
	kh_del (sht, ht, hit);
      else
	{
	  int ret;
	  kh_put (sht, ht, keys [i], & ret);
	  kh_value (ht, hit) = i;
	}
    }

  count = kh_size (ht);

  kh_destroy (sht, ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
