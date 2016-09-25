
unsigned udb_int (unsigned n, unsigned * keys)
{
  GHashTable * ht = g_hash_table_new (g_int_hash, g_int_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (g_hash_table_contains (ht, & keys [i]))
	g_hash_table_remove (ht, & keys [i]);
      else
	g_hash_table_insert (ht, (gpointer) & keys [i], (gpointer) & keys [i]);
    }

  count = g_hash_table_size (ht);

  g_hash_table_destroy (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  GHashTable * ht = g_hash_table_new (g_str_hash, g_str_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (g_hash_table_contains (ht, keys [i]))
	g_hash_table_remove (ht, keys [i]);
      else
	g_hash_table_insert (ht, (gpointer) keys [i], (gpointer) keys [i]);
    }

  count = g_hash_table_size (ht);

  g_hash_table_destroy (ht);

  return count;
}
