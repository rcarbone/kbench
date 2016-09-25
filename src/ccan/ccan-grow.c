
unsigned grow_int (unsigned n, unsigned * keys)
{
  struct htable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  htable_init (ht, hash_int_fn, NULL);

  for (i = 0; i < n; i ++)
    htable_add (ht, keys [i], & keys [i]);

  count = htable_count (ht);

  htable_clear (ht);
  free (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  struct htable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  htable_init (ht, hash_str_fn, NULL);

  for (i = 0; i < n; i ++)
    htable_add (ht, hash_string (keys [i]), keys [i]);

  count = htable_count (ht);

  htable_clear (ht);
  free (ht);

  return count;
}
