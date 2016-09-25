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

#include "google-dense-udb.c"
#include "google-dense-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
