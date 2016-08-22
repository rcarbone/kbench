#include <stdlib.h>

#include "benchmark.h"

/* The implementation */
#include <tcl.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned Tcl_SizeHashTable (Tcl_HashTable * ht)
{
  return ht -> numEntries;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  Tcl_HashTable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  Tcl_InitHashTable (ht, TCL_ONE_WORD_KEYS);

  for (i = 0; i < n; i ++)
    {
      Tcl_HashEntry * he = Tcl_FindHashEntry (ht, keys [i]);
      if (he)
	Tcl_DeleteHashEntry (he);
      else
	{
	  int new_val;
	  Tcl_HashEntry * he = Tcl_CreateHashEntry (ht, keys [i], & new_val);
	  Tcl_SetHashValue (he, (ClientData) & keys [i]);
	}
    }

  count = Tcl_SizeHashTable (ht);

  Tcl_DeleteHashTable (ht);
  free (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  Tcl_HashTable * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  Tcl_InitHashTable (ht, TCL_STRING_KEYS);

  for (i = 0; i < n; i ++)
    {
      Tcl_HashEntry * he = Tcl_FindHashEntry (ht, keys [i]);
      if (he)
	Tcl_DeleteHashEntry (he);
      else
	{
	  int new_val;
	  Tcl_HashEntry * he = Tcl_CreateHashEntry (ht, keys [i], & new_val);
	  Tcl_SetHashValue (he, (ClientData) & i);
	}
    }

  count = Tcl_SizeHashTable (ht);

  Tcl_DeleteHashTable (ht);
  free (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
