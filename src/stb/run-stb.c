#include "benchmark.h"

/* The implementation */
#define STB_DEFINE
#include "stb.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  stb_idict * ht = stb_idict_create ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      int hit;
      if (stb_idict_get_flag (ht, keys [i], & hit))
	stb_idict_remove (ht, keys [i], & hit);
      else
	stb_idict_set (ht, keys [i], keys [i]);
    }

  count = ht -> count;

  stb_idict_destroy (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  stb_sdict * ht = stb_sdict_new (0);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (stb_sdict_get (ht, keys [i]))
	stb_sdict_remove (ht, keys [i], NULL);
      else
	stb_sdict_set (ht, keys [i], & i);
    }

  count = ht -> count;

  stb_sdict_destroy (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
