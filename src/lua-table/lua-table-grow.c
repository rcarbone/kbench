
unsigned grow_int (unsigned n, unsigned * keys)
{
  table_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    table_set (ht, keys [i], keys [i]);

  count = table_count (ht);

  table_destroy (ht);
  free (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  table_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    table_set (ht, (hvalue_t) keys [i], i + 1);

  count = table_count (ht);

  table_destroy (ht);
  free (ht);

  return count;
}
