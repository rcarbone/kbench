
unsigned grow_int (unsigned n, unsigned * keys)
{
  struct HashTable * ht = AllocateHashTable (sizeof (unsigned), DONTCOPY);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    HashInsert (ht, keys [i], keys [i]);

  count = HashCount (ht);

  FreeHashTable (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  struct HashTable * ht = AllocateHashTable (0, DONTCOPY);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    HashInsert (ht, (ulong) keys [i], i);

  count = HashCount (ht);

  FreeHashTable (ht);

  return count;
}
