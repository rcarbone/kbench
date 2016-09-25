
unsigned udb_int (unsigned n, unsigned * keys)
{
  struct hashtable * ht = create_hashtable (0, hash_int_key_fn, eq_int_key_fn);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hashtable_search (ht, & keys [i]))
	hashtable_remove (ht, & keys [i]);
      else
	hashtable_insert (ht, & keys [i], & i);
    }

  count = hashtable_count (ht);

  hashtable_destroy (ht, 0);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  struct hashtable * ht = create_hashtable (0, hash_str_key_fn, eq_str_key_fn);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hashtable_search (ht, keys [i]))
	hashtable_remove (ht, keys [i]);
      else
	hashtable_insert (ht, keys [i], & i);
    }

  count = hashtable_count (ht);

  hashtable_destroy (ht, 0);

  return count;
}
