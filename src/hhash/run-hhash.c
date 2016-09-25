#include <stdio.h>

#include "benchmark.h"

/* The implementation */
#include "hhash.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned hhashcount (HHash * ht)
{
  return ht -> m;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "hhash-udb.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, NULL, NULL, NULL);
}
