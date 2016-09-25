#include <string>

#include "benchmark.h"

/* The implementation */
#include "sparsehash/dense_hash_map"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef google::dense_hash_map<unsigned, unsigned> hashtable_int_t;
typedef google::dense_hash_map<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "dense-udb.cpp"
#include "dense-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
