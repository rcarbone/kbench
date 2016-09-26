#include "benchmark.h"

/* The implementation */
#include "uthash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef struct ht ht_t;
struct ht
{
  unsigned key;
  char str [16];
  unsigned val;

  UT_hash_handle hh;     /* field must be named hh in order to use the convenience macros */
};

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "uthash-udb.c"
#include "uthash-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
