#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "hashit.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define H_HT_TYPE  OVERFLOW_H

static int cmp_int_fn (void * a, void * b)
{
  return a && b ? * (unsigned *) a - * (unsigned *) b : 1;
}


static int cmp_str_fn (void * a, void * b)
{
  return a && b ? strcmp (a, b) : 1;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "hashit-overflow-udb.c"
#include "hashit-overflow-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
