#include <stdio.h>

#include "benchmark.h"

/* The implementation */
#define __USE_LARGEFILE64
#include <apr-1.0/apr_hash.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define apr_hash_del(x, y, z)  apr_hash_set(x, y, z, NULL)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "apr-udb.c"
#include "apr-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
