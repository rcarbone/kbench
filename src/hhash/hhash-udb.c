
unsigned udb_int (unsigned n, unsigned * keys)
{
  /* Warning: 0 cannot be used as value */
  HHash * ht = hhashnew (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (hhashget (ht, keys [i], 0))
	hhashdel (ht, keys [i], 0);
      else
	hhashput (ht, keys [i], keys [i]);
    }

  count = hhashcount (ht);

  hhashfree (ht);

  return count;
}

