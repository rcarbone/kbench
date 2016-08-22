#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "htable.h"
#include "hash.h"


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Hash is simply key itself */
static size_t hash_int_fn (const void * key, void * unused)
{
  return * (unsigned *) key;
}


static bool eq_int_fn (const void * a, void * b)
{
  return * (unsigned *) a == * (unsigned *) b;
}


static size_t hash_str_fn (const void * key, void * unused)
{
  return hash_string (key);
}


static bool eq_str_fn (const void * a, void * b)
{
  return ! strcmp (a, b);
}


static unsigned htable_count (struct htable * ht)
{
  return ht -> elems;
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  struct htable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  htable_init (ht, hash_int_fn, NULL);

  for (i = 0; i < n; i ++)
    {
      unsigned * hit = htable_get (ht, keys [i], eq_int_fn, & keys [i]);
      if (hit)
	htable_del (ht, keys [i], hit);
      else
	htable_add (ht, keys [i], & keys [i]);
    }

  count = htable_count (ht);

  htable_clear (ht);
  free (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  struct htable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  htable_init (ht, hash_str_fn, NULL);

  for (i = 0; i < n; i ++)
    {
      unsigned * hit = htable_get (ht, hash_string (keys [i]), eq_str_fn, keys [i]);
      if (hit)
	htable_del (ht, hash_string (keys [i]), hit);
      else
	htable_add (ht, hash_string (keys [i]), keys [i]);
    }

  count = htable_count (ht);

  htable_clear (ht);
  free (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
