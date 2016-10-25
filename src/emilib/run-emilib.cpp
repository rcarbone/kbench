#include <stdint.h>
#include <string.h>

#include "benchmark.h"
#include "rhash.h"

/* The implementation */
#define LOGURU_IMPLEMENTATION 0
#include "hash_map.hpp"
using namespace emilib;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef emilib::HashMap<unsigned,    unsigned> hashtable_int_t;
typedef emilib::HashMap<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "udb.cpp"
#include "grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
