#include "benchmark.h"

/* The implementation */
#include <unordered_map>
#include <string>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef std::unordered_map<unsigned, unsigned> hashtable_int_t;
typedef std::unordered_map<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "g++-unordered-udb.cpp"
#include "g++-unordered-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
