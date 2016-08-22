#include <stdio.h>

#include "benchmark.h"

/* The implementation */
#define Table(x) Dense##x           /* Google Dense tables */
#include "libchash.h"


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define DONTCOPY  0

static unsigned HashCount (struct HashTable * ht)
{
  return ht -> cItems;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  struct HashTable * ht = AllocateHashTable (sizeof (unsigned), DONTCOPY);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (HashFind (ht, keys [i]))
	HashDelete (ht, keys [i]);
      else
	HashInsert (ht, keys [i], keys [i]);
    }

  count = HashCount (ht);

  FreeHashTable (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  struct HashTable * ht = AllocateHashTable (0, DONTCOPY);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (HashFind (ht, (ulong) keys [i]))
	HashDelete (ht, (ulong) keys [i]);
      else
	HashInsert (ht, (ulong) keys [i], i);
    }

  count = HashCount (ht);

  FreeHashTable (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
