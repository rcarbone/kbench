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

#include "tcl-udb.c"
#include "tcl-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
