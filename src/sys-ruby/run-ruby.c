#include "benchmark.h"

/* The implementation */
#include <ruby.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
{
  VALUE ht;
  unsigned i;
  unsigned count;

  ruby_setup ();
#if defined(ROCCO)
  rb_protect (key_not_found, (VALUE) NULL, 0);
#endif /* ROCCO */
  ht = rb_hash_new ();

  for (i = 0; i < n; i ++)
    {
      VALUE hit = rb_hash_fetch (ht, INT2NUM (keys [i]));
      if (hit)
	rb_hash_delete (ht, INT2NUM (keys [i]));
      else
	rb_hash_aset (ht, INT2NUM (keys [i]), INT2NUM (keys [i]));
    }

  count = RHASH_SIZE (ht);

  rb_hash_clear (ht);
  ruby_finalize ();

  return count;
}


int udb_str (int n, char * const * keys)
{
  VALUE ht;
  unsigned i;
  unsigned count;

  ruby_setup ();
  ht = rb_hash_new ();

  for (i = 0; i < n; i ++)
    {
      VALUE hit = rb_hash_fetch (ht, rb_str_new2 (keys [i]));
      if (hit)
	rb_hash_delete (ht, rb_str_new2 (keys [i]));
      else
	rb_hash_aset (ht, rb_str_new2 (keys [i]), INT2NUM (i));
    }

  count = RHASH_SIZE (ht);

  rb_hash_clear (ht);
  ruby_finalize ();

  return count;
}


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
