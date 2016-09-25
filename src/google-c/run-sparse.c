#include <stdio.h>

#include "benchmark.h"

/* The implementation */
#define Table(x) Sparse##x          /* Google Sparse tables */
#include "libchash.h"


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define DONTCOPY  0

static unsigned HashCount (struct HashTable * ht)
{
  return ht -> cItems;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "google-sparse-udb.c"
#include "google-sparse-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
