
unsigned udb_int (unsigned n, unsigned * keys)
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


unsigned udb_str (unsigned n, char ** keys)
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
