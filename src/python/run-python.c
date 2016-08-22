#include "benchmark.h"

/* The implementation */
#include "hashtable.h"
#include "rhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define INT_VAL_SIZE sizeof (unsigned)

static Py_uhash_t _Py_hashtable_hash_str (const void * key)
{
  return python_hash (key);
}


static int _Py_hashtable_compare_string (const void * key, const _Py_hashtable_entry_t * entry)
{
  return ! strcmp (entry -> key, key);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  _Py_hashtable_t * ht = _Py_hashtable_new (INT_VAL_SIZE, _Py_hashtable_hash_int, _Py_hashtable_compare_direct);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (_Py_hashtable_get_entry (ht, (const void *) keys [i]))
	_Py_hashtable_delete (ht, (const void *) keys [i]);
      else
	_Py_HASHTABLE_SET (ht, (const void *) keys [i], i);
    }

  count = ht -> entries;

  _Py_hashtable_destroy (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  _Py_hashtable_t * ht = _Py_hashtable_new (INT_VAL_SIZE, _Py_hashtable_hash_str, _Py_hashtable_compare_string);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (_Py_hashtable_get_entry (ht, keys [i]))
	_Py_hashtable_delete (ht, keys [i]);
      else
	_Py_HASHTABLE_SET (ht, keys [i], i);
    }

  count = ht -> entries;

  _Py_hashtable_destroy (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
