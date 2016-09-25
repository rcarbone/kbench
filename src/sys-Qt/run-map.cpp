#include "benchmark.h"

/* The implementation */
#include <QtCore/QMap>
#include <string>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

typedef QMap<unsigned, unsigned> hashtable_int_t;
typedef QMap<std::string, unsigned> hashtable_str_t;

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "qt-map-udb.cpp"
#include "qt-map-grow.cpp"


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str, grow_int, grow_str);
}
