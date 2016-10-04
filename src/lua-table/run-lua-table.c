#include <stdio.h>
#include <stdlib.h>

#include "benchmark.h"

/* The implementation */
#include "table.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static int32_t table_count (table_t * ht)
{
  unsigned count = 0;
  int32_t i = (1 << ht -> nodes_size_log) - 1;

  while (i >= 0)
    {
      table_node_t * node = & ht -> nodes [i --];
      if (node -> active)
	count ++;
    }
  return count;
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "lua-table-udb.c"
#include "lua-table-grow.c"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
