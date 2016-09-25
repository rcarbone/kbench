
unsigned grow_int (unsigned n, unsigned * keys)
{
  khash_t(uht) * ht = kh_init (uht);
  unsigned i;
  int ret;
  unsigned count;

  printf ("GROW\n");

  for (i = 0; i < n; i ++)
    {
      khiter_t hit = kh_put (uht, ht, keys [i], & ret);
      kh_value (ht, hit) = i + 1;
    }

  count = kh_size (ht);

  kh_destroy (uht, ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  khash_t(sht) * ht = kh_init (sht);
  unsigned i;
  int ret;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      khiter_t hit = kh_put (sht, ht, keys [i], & ret);
      kh_value (ht, hit) = i + 1;
    }

  count = kh_size (ht);

  kh_destroy (sht, ht);

  return count;
}
