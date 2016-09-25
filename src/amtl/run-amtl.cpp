#include <string>

#include "benchmark.h"

/* The implementation */
#include "amtl/am-hashmap.h"
#include "amtl/am-string.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

using namespace ke;

struct Policy
{
  static inline uint32_t hash (unsigned key)
  {
    return HashInt64 (key);
  }

  static inline uint32_t hash (const char * key)
  {
    return FastHashCharSequence (key, strlen (key));
  }

  static inline bool matches (unsigned key1, unsigned key2)
  {
    return key1 == key2;
  }

  static inline bool matches (const char * find, const AString & key)
  {
    return key . compare (find) == 0;
  }
};

typedef ke::HashMap<unsigned, unsigned, Policy> hashtable_int_t;
typedef ke::HashMap<ke::AString, unsigned, Policy> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "amtl-udb.cpp"
#include "amtl-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
