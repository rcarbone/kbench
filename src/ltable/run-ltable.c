#include <stdio.h>
#include <stdlib.h>

#include "benchmark.h"

/* The implementation */
#include "ltable.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned ltable_count (struct ltable * ht)
{
  unsigned count = 0;
  unsigned i;
  int * p;
  struct ltable_key kp;

  i = 0;
  while ((p = ltable_next (ht, & i, & kp)))
    count ++;
  return count;
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "ltable-udb.c"
#include "ltable-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
