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
typedef rde::hash_map<const char *, unsigned, hasher, 6, eqstr> hashtable_str_t;

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
	ht -> insert (rde::pair<unsigned, unsigned> (keys [i], i));
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
	ht -> insert (rde::pair<const char *, unsigned> (keys [i], i));
    }

  count = ht -> size ();

  delete ht;

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
