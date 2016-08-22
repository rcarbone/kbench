#include <stdio.h>
#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "hashtab.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "rhash.h"

static hashval_t hash_int_fn (const void * key)
{
  return java_hash (* (unsigned *) key);
}


static int eq_int_fn (const void * key1, const void * key2)
{
  return * (unsigned *) key1 == * (unsigned *) key2;
}


static hashval_t hash_str_fn (const void * key)
{
  return python_hash (key);
}


static int eq_str_fn (const void * key1, const void * key2)
{
  return ! strcmp (key1, key2);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  htab_t ht = htab_create (0, hash_int_fn, eq_int_fn, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (htab_find (ht, & keys [i]))
	htab_remove_elt (ht, (void *) & keys [i]);
      else
	{
	  void ** elem = htab_find_slot (ht, & keys [i], INSERT);
	  if (elem)
	    * elem = (void *) & keys [i];
	}
    }

  count = htab_elements (ht);

  htab_delete (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  htab_t ht = htab_create (0, hash_str_fn, eq_str_fn, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (htab_find (ht, keys [i]))
	htab_remove_elt (ht, keys [i]);
      else
	{
	  void ** elem = htab_find_slot (ht, keys [i], INSERT);
	  if (elem)
	    * elem = (void *) keys [i];
	}
    }

  count = htab_elements (ht);

  htab_delete (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
