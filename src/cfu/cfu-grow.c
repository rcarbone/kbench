
unsigned grow_int (unsigned n, unsigned * keys)
{
  cfuhash_table_t * ht = cfuhash_new ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    cfuhash_put_data (ht, & keys [i], sizeof (keys [i]), & i, sizeof (i), NULL);

  count = cfuhash_num_entries (ht);

  cfuhash_destroy (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  cfuhash_table_t * ht = cfuhash_new ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    cfuhash_put (ht, keys [i], & i);

  count = cfuhash_num_entries (ht);

  cfuhash_destroy (ht);

  return count;
}
