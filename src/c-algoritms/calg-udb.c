
unsigned udb_int (unsigned n, unsigned * keys)
{
  HashTable * ht = hash_table_new (int_hash, int_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hash_table_lookup (ht, (unsigned *) & keys [i]))
	hash_table_remove (ht, (unsigned *) & keys [i]);
      else
	hash_table_insert (ht, (unsigned *) & keys [i], & i);
    }

  count = hash_table_num_entries (ht);

  hash_table_free (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  HashTable * ht = hash_table_new (string_hash, string_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hash_table_lookup (ht, keys [i]))
	hash_table_remove (ht, keys [i]);
      else
	hash_table_insert (ht, keys [i], & i);
    }

  count = hash_table_num_entries (ht);

  hash_table_free (ht);

  return count;
}
