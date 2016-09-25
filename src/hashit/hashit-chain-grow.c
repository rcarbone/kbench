
unsigned grow_int (unsigned n, unsigned * keys)
{
  hash_t ht = hashit_create (n, sizeof (unsigned), NULL, cmp_int_fn, H_HT_TYPE);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    hashit_insert (ht, (unsigned *) & keys [i], & i);

  count = hashit_size (ht);

  hashit_destroy (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  hash_t ht = hashit_create (n, 0, NULL, cmp_str_fn, H_HT_TYPE);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    hashit_insert (ht, keys [i], & i);

  count = hashit_size (ht);

  hashit_destroy (ht);

  return count;
}
