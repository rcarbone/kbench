#include <stdint.h>
#include <string.h>
#include <math.h>

#include "benchmark.h"
#include "rhash.h"

/* The implementation */
static bool _antiresize_recursion = false;
#include <hashmap.hpp>

using namespace container;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef container::hash_map<unsigned, unsigned>    hashtable_int_t;
typedef container::hash_map<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "udb.cpp"
#include "grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
