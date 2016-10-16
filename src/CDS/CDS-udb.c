
unsigned udb_int (unsigned n, unsigned * keys)
{
  HashMap * ht = HashMapInit ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (HashMapContain (ht, (void *) (intptr_t) keys [i]))
	HashMapRemove (ht, (void *) (intptr_t) keys [i]);
      else
	HashMapPut (ht, (void *) (intptr_t) keys [i], (void *) (intptr_t) keys [i]);
    }

  count = HashMapSize (ht);

  HashMapDeinit (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  HashMap * ht = HashMapInit ();
  unsigned i;
  unsigned count;

  /* Set the custom hash value generator and key comparison functions */
  HashMapSetHash (ht, HashKey);
  HashMapSetCompare (ht, CompareKey);

  for (i = 0; i < n; i ++)
    {
      if (HashMapContain (ht, keys [i]))
	HashMapRemove (ht, keys [i]);
      else
	HashMapPut (ht, keys [i], & i);
    }

  count = HashMapSize (ht);

  HashMapDeinit (ht);

  return count;
}
