#include "benchmark.h"

/* The implementation */
#include <QtCore/QHash>
#include <string>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

struct mystr_t
{
  const char * str;
};

typedef QHash<unsigned, unsigned> hashtable_int_t;
typedef QHash<mystr_t, unsigned> hashtable_str_t;

inline bool operator == (const mystr_t & a, const mystr_t & b) { return strcmp (a . str, b . str) == 0; }

static inline unsigned __ac_X31_hash_string (const char * s)
{
  unsigned h = * s;
  if (h)
    for (++ s; * s; ++ s)
      h = (h << 5) - h + * s;
  return h;
}


inline uint qHash (const mystr_t & a)
{
  return __ac_X31_hash_string (a . str);
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      hashtable_int_t::const_iterator hit = ht -> find (keys [i]);
      if (hit != ht -> end ())
	ht -> remove (keys [i]);
      else
	ht -> insert (keys [i], keys [i]);
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
      mystr_t p;
      hashtable_str_t::const_iterator hit;

      p . str = keys [i];
      hit = ht -> find (p);
      if (hit != ht -> end ())
	ht -> remove (p);
      else
	ht -> insert (p, i);
    }

  count = ht -> size ();

  delete ht;

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
