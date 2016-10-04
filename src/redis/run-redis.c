#include <stdio.h>
#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "dict.h"

#define _serverAssert(x, y, z) assert(x)

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "udb.c"
#if defined(ROCCO)
#include "redis-grow.c"
#endif /* ROCCO */

int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, NULL, NULL);
}
