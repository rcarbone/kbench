
unsigned grow_int (unsigned n, unsigned * keys)
{
  struct ltable * ht = ltable_create (sizeof (unsigned), 0);
  unsigned i;
  unsigned count;
  struct ltable_key key;
  unsigned * val;

  for (i = 0; i < n; i ++)
    {
      val = ltable_set (ht, ltable_numkey (& key, keys [i]));
      * val = keys [i];
    }

  count = ltable_count (ht);

  ltable_release (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  struct ltable * ht = ltable_create (sizeof (unsigned), 0);
  unsigned i;
  unsigned count;
  struct ltable_key key;
  unsigned * val;

  for (i = 0; i < n; i ++)
    {
      val = ltable_set (ht, ltable_strkey (& key, keys [i]));
      * val = i + 1;
    }

  count = ltable_count (ht);

  ltable_release (ht);

  return count;
}
