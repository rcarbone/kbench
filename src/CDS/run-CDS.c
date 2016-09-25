#include "benchmark.h"

/* The implementation */
#include "hash_map.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned HashDjb2 (char * key)
{
  unsigned hash = 5381;
  int c;

  while ((c = * key ++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}


static unsigned HashKey (void * key)
{
  return HashDjb2 ((char *) key);
}


static int CompareKey (void * lhs, void * rhs)
{
  return strcmp ((char *) lhs, (char *) rhs);
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "CDS-udb.c"
#include "CDS-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
