#include "benchmark.h"

/* The implementation */
#define inline
#include "htable.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define INITIAL_SIZE 127

typedef struct
{
  unsigned uval;
  char sval [16];

  struct hash_entry _reserved_;    /* field required to make the object hash-able */
} item_t;


/* Compare two integer values */
static int cmp_int (const void * a, const void * b, size_t len)
{
  return * (unsigned *) a - * (unsigned *) b;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "htable-udb.c"
#include "htable-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
