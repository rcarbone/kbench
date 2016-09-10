#include <stdlib.h>
#include <string>

#include "benchmark.h"

/* The implementation */
#include "EASTL/hash_map.h"
#include "hashtable.cpp"

/* operator new required by EASTL */
#define THROW_SPEC_0    // Throw 0 arguments
#define THROW_SPEC_1(x) // Throw 1 argument

/* Stolen from doc/SampleNewAndDelete.cpp */
void * operator new [] (size_t size, const char* /*name*/, int /*flags*/, 
			unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) THROW_SPEC_1(std::bad_alloc)
{
  return calloc (1, size);
}


void* operator new [] (size_t size, size_t alignment, size_t alignmentOffset, const char* /*name*/, 
		       int flags, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) THROW_SPEC_1(std::bad_alloc)
{
  // Substitute your aligned malloc. 
#define malloc_aligned(x, y, z) calloc(1, x)
  return malloc_aligned(size, alignment, alignmentOffset);
}


/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Stolen from benchmark/source/BenchmarkHash.cpp */
// HashString8
//
// We define a string
//
template <typename String>
struct HashString8
{
  // Defined for EASTL, STLPort, SGI, etc. and Metrowerks-related hash tables:
  size_t operator () (const String & s) const 
  { 
    const uint8_t * p = (const uint8_t *) s . c_str();
    uint32_t c, stringHash = UINT32_C (2166136261);
    while((c = * p ++) != 0)
      stringHash = (stringHash * 16777619) ^ c;
    return stringHash;
  }

  // Defined for Dinkumware-related (e.g. MS STL) hash tables:
  bool operator() (const String & s1, const String & s2) const
  {
    return s1 < s2;
  }

  // Defined for Dinkumware-related (e.g. MS STL) hash tables:
  enum
    {
      bucket_size = 7,
      min_buckets = 8
    };
};

typedef eastl::hash_map<unsigned, unsigned> hashtable_int_t;
typedef eastl::hash_map<std::string, unsigned, HashString8<std::string>> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      hashtable_int_t::iterator hit = ht -> find (keys [i]);
      if (hit != ht -> end ())
	ht -> erase (hit);
      else
	ht -> insert (hashtable_int_t::value_type (keys [i], keys [i]));
    }

  count = ht -> size ();

  delete ht;

  return count;
}


int udb_str (int n, char * const * keys)
{
  hashtable_str_t * ht = new hashtable_str_t;
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      hashtable_str_t::iterator hit = ht -> find (keys [i]);
      if (hit != ht -> end ())
	ht -> erase (hit);
      else
	ht -> insert (hashtable_str_t::value_type (keys [i], i));
    }

  count = ht -> size ();

  delete ht;

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
