#include <string>

#include "benchmark.h"

/* The implementation */
#include "amtl/am-hashmap.h"
#include "amtl/am-string.h"

using namespace ke;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

int udb_int (int n, const unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  ht -> init ();

  for (i = 0; i < n; i ++)
    {
      hashtable_int_t::Insert hit = ht -> findForAdd (keys [i]);
      if (hit . found ())
	ht -> remove (hit);
      else
	ht -> add (hit, keys [i], i);
    }

  count = ht -> elements ();

  delete ht;

  return count;
}


int udb_str (int n, char * const * keys)
{
  hashtable_str_t * ht = new hashtable_str_t;
  unsigned i;
  unsigned count;

  ht -> init ();

  for (i = 0; i < n; i ++)
    {
      hashtable_str_t::Insert hit = ht -> findForAdd (keys [i]);
      if (hit . found ())
	ht -> remove (hit);
      else
	ht -> add (hit, AString (keys [i]), i);
    }

  count = ht -> elements ();

  delete ht;

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
