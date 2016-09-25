
unsigned grow_int (unsigned n, unsigned * keys)
{
  HashMap * ht = HashMapInit ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    HashMapPut (ht, (void *) (intptr_t) keys [i], (void *) (intptr_t) keys [i]);

  count = HashMapSize (ht);

  HashMapDeinit (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  HashMap * ht = HashMapInit ();
  unsigned i;
  unsigned count;

  /* Set the custom hash value generator and key comparison functions */
  HashMapSetHash (ht, HashKey);
  HashMapSetCompare (ht, CompareKey);

  for (i = 0; i < n; i ++)
    HashMapPut (ht, keys [i], & i);

  count = HashMapSize (ht);

  HashMapDeinit (ht);

  return count;
}
