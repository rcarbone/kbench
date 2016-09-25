
unsigned grow_int (unsigned n, unsigned * keys)
{
  openhash_t(uht_t) * ht = openhash_init (uht_t);
  unsigned i;
  int ret;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      oh_iter_t hi = openhash_set (uht_t, ht, keys [i], & ret);
      openhash_value (ht, hi) = keys [i];
    }

  count = openhash_size (ht);

  openhash_destroy (uht_t, ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  openhash_t(sht_t) * ht = openhash_init (sht_t);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      oh_iter_t hi = openhash_get (sht_t, ht, keys [i]);
      if (hi != openhash_end (ht))
	openhash_del (sht_t, ht, hi);
      else
	{
	  int ret;
	  hi = openhash_set (sht_t, ht, keys [i], & ret);
	  openhash_value (ht, hi) = i;
	}
    }

  count = openhash_size (ht);

  openhash_destroy (sht_t, ht);

  return count;
}
