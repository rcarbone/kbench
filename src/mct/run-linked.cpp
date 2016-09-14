#include <stdlib.h>
#include <string>

#include "benchmark.h"

/* The implementation */
#include "mct/hash-map.hpp"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef mct::linked_hash_map<unsigned, unsigned> hashtable_int_t;
typedef mct::linked_hash_map<std::string, unsigned> hashtable_str_t;

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
