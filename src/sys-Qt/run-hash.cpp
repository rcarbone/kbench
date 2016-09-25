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

#include "qt-hash-udb.cpp"
#include "qt-hash-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
