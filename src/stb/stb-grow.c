
unsigned grow_int (unsigned n, unsigned * keys)
{
  stb_idict * ht = stb_idict_create ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    stb_idict_set (ht, keys [i], keys [i]);

  count = ht -> count;

  stb_idict_destroy (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  stb_sdict * ht = stb_sdict_new (0);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    stb_sdict_set (ht, keys [i], & i);

  count = ht -> count;

  stb_sdict_destroy (ht);

  return count;
}
