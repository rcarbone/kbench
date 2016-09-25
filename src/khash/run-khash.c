#include "benchmark.h"

/* The implementation */
#include "khash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Instantiate structs and methods */
KHASH_MAP_INIT_INT(uht_t, unsigned)
KHASH_MAP_INIT_STR(sht_t, unsigned)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "khash-udb.c"
#include "khash-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
