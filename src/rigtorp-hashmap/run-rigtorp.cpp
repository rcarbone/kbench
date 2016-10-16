#include <stdint.h>
#include <string.h>

#include "benchmark.h"
#include "rhash.h"

/* The implementation */
#include "HashMap.h"
using namespace rigtorp;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

struct hasher
{
#if defined(ROCCO)
  inline rde::hash_value_t operator () (const char * s) const
  {
    rde::hash_value_t hash (0);
    char c;
    while ((c = * s ++) != 0)
      hash = (hash << 5) + hash + c;
    return hash;
  }
#else
  unsigned operator () (char * key) { return python_hash (key); }
#endif /* ROCCO */
};


struct equaler
{
  inline bool operator () (char * s1, char * s2)
  {
    return ! strcmp (s1, s2);
  }
};


typedef rigtorp::HashMap<unsigned, unsigned>                hashtable_int_t;
typedef rigtorp::HashMap<char *, unsigned, hasher, equaler> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "udb.cpp"
#include "grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
