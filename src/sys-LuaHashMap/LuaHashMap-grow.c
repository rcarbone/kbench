
unsigned grow_int (unsigned n, unsigned * keys)
{
  LuaHashMap * ht = LuaHashMap_Create ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    LuaHashMap_SetValueIntegerForKeyInteger (ht, keys [i], keys [i]);

  count = LuaHashMap_Count (ht);

  LuaHashMap_Free (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  LuaHashMap * ht = LuaHashMap_Create ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    LuaHashMap_SetValueIntegerForKeyString (ht, i, keys [i]);

  count = LuaHashMap_Count (ht);

  LuaHashMap_Free (ht);

  return count;
}
