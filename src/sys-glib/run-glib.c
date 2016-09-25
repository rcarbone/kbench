#include "benchmark.h"

/* The implementation */
#include "glib.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "glib-udb.c"
#include "glib-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
