
unsigned udb_int (unsigned n, unsigned * keys)
{
  dict * ht = dictCreate (& int_dict, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (dictFind (ht, (void *) keys [i]))
	dictDelete (ht, (void *) keys [i]);
      else
	dictAdd (ht, (void *) keys [i], (void *) keys [i]);
    }

  count = dictSize (ht);

  dictRelease (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  dict * ht = dictCreate (& str_dict, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (dictFind (ht, keys [i]))
	dictDelete (ht, keys [i]);
      else
	dictAdd (ht, keys [i], (void *) i);
    }

  count = dictSize (ht);

  dictRelease (ht);

  return count;
}
