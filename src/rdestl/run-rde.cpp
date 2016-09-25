#include <stdint.h>
#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "hash_map.h"


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

struct eqstr
{
  inline bool operator () (const char * s1, const char * s2) const
  {
    return strcmp (s1, s2) == 0;
  }
};


struct hasher
{
  inline rde::hash_value_t operator () (const char * s) const
  {
    rde::hash_value_t hash (0);
    char c;
    while ((c = * s ++) != 0)
      hash = (hash << 5) + hash + c;
    return hash;
  }
};


typedef rde::hash_map<unsigned, unsigned> hashtable_int_t;
typedef rde::hash_map<char *, unsigned, hasher, 6, eqstr> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "rde-udb.cpp"
#include "rde-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
