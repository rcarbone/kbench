#include "benchmark.h"

/* The implementation */
#include <EXTERN.h>
#include <perl.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  PerlInterpreter * my_perl = perl_alloc ();
  HV * ht;
  unsigned i;
  unsigned count;

  perl_construct (my_perl);
  ht = newHV ();

  for (i = 0; i < n; i ++)
    {
      SV * key = newSViv (keys [i]);
      if (hv_fetch_ent (ht, key, 0, 0))
	hv_delete_ent (ht, key, G_DISCARD, 0);
      else
	{
	  SV * val = newSViv (keys [i]);
	  hv_store_ent (ht, key, val, 0);
	}
    }

  count = HvKEYS (ht);

  hv_clear (ht);
  perl_destruct (my_perl);
  perl_free (my_perl);

  return count;
}


int udb_str (int n, char * const * keys)
{
  PerlInterpreter * my_perl = perl_alloc ();
  HV * ht = newHV ();
  unsigned i;
  unsigned count;

  perl_construct (my_perl);

  for (i = 0; i < n; i ++)
    {
      if (hv_fetch (ht, keys [i], strlen (keys [i]), 0))
	hv_delete (ht, keys [i], strlen (keys [i]), G_DISCARD);
      else
	{
	  SV * val = newSViv (i);
	  hv_store (ht, keys [i], strlen (keys [i]), val, 0);
	}
    }

  count = HvKEYS (ht);

  hv_clear (ht);
  perl_destruct (my_perl);
  perl_free (my_perl);

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
