
unsigned udb_int (unsigned n, unsigned * keys)
{
  struct htable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  htable_init (ht, hash_int_fn, NULL);

  for (i = 0; i < n; i ++)
    {
      unsigned * hit = htable_get (ht, keys [i], eq_int_fn, & keys [i]);
      if (hit)
	htable_del (ht, keys [i], hit);
      else
	htable_add (ht, keys [i], & keys [i]);
    }

  count = htable_count (ht);

  htable_clear (ht);
  free (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  struct htable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  htable_init (ht, hash_str_fn, NULL);

  for (i = 0; i < n; i ++)
    {
      unsigned * hit = htable_get (ht, hash_string (keys [i]), eq_str_fn, keys [i]);
      if (hit)
	htable_del (ht, hash_string (keys [i]), hit);
      else
	htable_add (ht, hash_string (keys [i]), keys [i]);
    }

  count = htable_count (ht);

  htable_clear (ht);
  free (ht);

  return count;
}
