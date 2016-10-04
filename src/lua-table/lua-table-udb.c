
unsigned udb_int (unsigned n, unsigned * keys)
{
  table_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  table_init (ht, H_INT64, NULL, NULL);

  for (i = 0; i < n; i ++)
    {
      if (table_contains (ht, keys [i]))
	table_delete (ht, keys [i]);
      else
	table_set (ht, keys [i], keys [i]);
    }

  count = table_count (ht);

  table_destroy (ht);
  free (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  table_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  table_init (ht, H_STRING, NULL, NULL);

  for (i = 0; i < n; i ++)
    {
      if (table_contains (ht, (hvalue_t) keys [i]))
	table_delete (ht, (hvalue_t) keys [i]);
      else
	table_set (ht, (hvalue_t) keys [i], i + 1);
    }

  count = table_count (ht);

  table_destroy (ht);
  free (ht);

  return count;
}
