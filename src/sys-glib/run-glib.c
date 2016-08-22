#include "benchmark.h"

/* The implementation */
#include "glib.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  GHashTable * ht = g_hash_table_new (g_int_hash, g_int_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (g_hash_table_contains (ht, & keys [i]))
	g_hash_table_remove (ht, & keys [i]);
      else
	g_hash_table_insert (ht, (gpointer) & keys [i], (gpointer) & keys [i]);
    }

  count = g_hash_table_size (ht);

  g_hash_table_destroy (ht);

  return count;
}


int udb_str (int n, char * const * keys)
{
  GHashTable * ht = g_hash_table_new (g_str_hash, g_str_equal);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (g_hash_table_contains (ht, keys [i]))
	g_hash_table_remove (ht, keys [i]);
      else
	g_hash_table_insert (ht, (gpointer) keys [i], (gpointer) keys [i]);
    }

  count = g_hash_table_size (ht);

  g_hash_table_destroy (ht);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
