#include <string.h>

#include "benchmark.h"

/* The implementation */
#include "ght_hash_table.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

static unsigned ght_count (ght_hash_table_t * ht)
{
  return ht -> i_items;
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  ght_hash_table_t * ht = ght_create (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (ght_get (ht, sizeof (keys [i]), & keys [i]))
	ght_remove (ht, sizeof (keys [i]), & keys [i]);
      else
	ght_insert (ht, (void *) & keys [i], sizeof (keys [i]), & keys [i]);
    }

  count = ght_count (ht);

  ght_finalize (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  ght_hash_table_t * ht = ght_create (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (ght_get (ht, strlen (keys [i]), keys [i]))
	ght_remove (ht, strlen (keys [i]), keys [i]);
      else
	ght_insert (ht, (void *) keys [i], strlen (keys [i]), keys [i]);
    }

  count = ght_count (ht);

  ght_finalize (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
