
unsigned udb_int (unsigned n, unsigned * keys)
{
  struct ltable * ht = ltable_create (sizeof (unsigned), 0);
  unsigned i;
  unsigned count;
  struct ltable_key key;
  unsigned * val;

  for (i = 0; i < n; i ++)
    {
      if (ltable_get (ht, ltable_intkey (& key, keys [i])))
	ltable_del (ht, ltable_intkey (& key, keys [i]));
      else
	{
	  val = ltable_set (ht, ltable_intkey (& key, keys [i]));
	  * val = keys [i];
	}
    }

  count = ltable_count (ht);

  ltable_release (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  struct ltable * ht = ltable_create (sizeof (unsigned), 0);
  unsigned i;
  unsigned count;
  struct ltable_key key;
  unsigned * val;

  for (i = 0; i < n; i ++)
    {
      if (ltable_get (ht, ltable_strkey (& key, keys [i])))
	ltable_del (ht, ltable_strkey (& key, keys [i]));
      else
	{
	  val = ltable_set (ht, ltable_strkey (& key, keys [i]));
	  * val = i + 1;
	}
    }

  count = ltable_count (ht);

  ltable_release (ht);

  return count;
}
