#include "benchmark.h"

/* The implementation */
#include "sparsehash/sparse_hash_map"
#include <string>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef google::sparse_hash_map<unsigned, unsigned> hashtable_int_t;
typedef google::sparse_hash_map<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "sparse-udb.cpp"
#include "sparse-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
