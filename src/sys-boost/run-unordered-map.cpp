#include "benchmark.h"

/* The implementation */
#include <boost/unordered_map.hpp>
#include <string>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef boost::unordered_map<unsigned, unsigned> hashtable_int_t;
typedef boost::unordered_map<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "boost-udb.cpp"
#include "boost-grow.cpp"

int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
