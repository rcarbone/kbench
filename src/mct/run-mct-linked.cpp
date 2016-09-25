#include <stdlib.h>
#include <string>

#include "benchmark.h"

/* The implementation */
#include "mct/hash-map.hpp"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef mct::linked_hash_map<unsigned, unsigned> hashtable_int_t;
typedef mct::linked_hash_map<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "mct-linked-udb.cpp"
#include "mct-linked-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
