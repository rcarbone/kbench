
unsigned udb_int (unsigned n, unsigned * keys)
{
  LuaHashMap * ht = LuaHashMap_Create ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (LuaHashMap_GetValueIntegerForKeyInteger (ht, keys [i]) == keys [i])
	LuaHashMap_RemoveKeyInteger (ht, keys [i]);
      else
	LuaHashMap_SetValueIntegerForKeyInteger (ht, keys [i], keys [i]);
    }

  count = LuaHashMap_Count (ht);

  LuaHashMap_Free (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  LuaHashMap * ht = LuaHashMap_Create ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (LuaHashMap_GetValueIntegerForKeyString (ht, keys [i]))
	LuaHashMap_RemoveKeyString (ht, keys [i]);
      else
	LuaHashMap_SetValueIntegerForKeyString (ht, i, keys [i]);
    }

  count = LuaHashMap_Count (ht);

  LuaHashMap_Free (ht);

  return count;
}
