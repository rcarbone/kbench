#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "ght_hash_table.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned ght_count (ght_hash_table_t * ht)
{
  return ht -> i_items;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "ght-udb.c"
#include "ght-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
