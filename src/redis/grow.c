
unsigned grow_int (unsigned n, unsigned * keys)
{
  dict * ht = dictCreate (& int_dict, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    dictAdd (ht, (void *) keys [i], (void *) keys [i]);

  count = dictSize (ht);

  dictRelease (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  dict * ht = dictCreate (& str_dict, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    dictAdd (ht, keys [i], (void *) i);

  count = dictSize (ht);

  dictRelease (ht);

  return count;
}
