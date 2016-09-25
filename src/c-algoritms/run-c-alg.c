#include "benchmark.h"

/* The implementation */
#include "hash-table.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "hash-int.h"
#include "compare-int.h"
#include "hash-string.h"
#include "compare-string.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "calg-udb.c"
#include "calg-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
