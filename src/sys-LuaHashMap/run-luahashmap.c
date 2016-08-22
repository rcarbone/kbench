#include "benchmark.h"

/* The implementation */
#include "LuaHashMap.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
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


int udb_str (int n, char * const * keys)
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


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
