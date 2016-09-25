
unsigned grow_int (unsigned n, unsigned * keys)
{
  HashTable * ht = hash_table_new (int_hash, int_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    hash_table_insert (ht, (unsigned *) & keys [i], & i);

  count = hash_table_num_entries (ht);

  hash_table_free (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  HashTable * ht = hash_table_new (string_hash, string_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    hash_table_insert (ht, keys [i], & i);

  count = hash_table_num_entries (ht);

  hash_table_free (ht);

  return count;
}
