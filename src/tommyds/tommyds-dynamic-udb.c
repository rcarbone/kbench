
unsigned udb_int (unsigned n, unsigned * keys)
{
  obj_t ** objs = setup_int_objs (n, keys);
  tommy_hashdyn * ht = tommy_hashdyn_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      unsigned key = java_hash (objs [i] -> ukey);
      if (tommy_hashdyn_search (ht, cmp_int, objs [i], key))
	tommy_hashdyn_remove (ht, cmp_int, objs [i], key);
      else
	tommy_hashdyn_insert (ht, & objs [i] -> _reserved_, objs [i], key);
    }

  count = tommy_hashdyn_count (ht);

  tommy_hashdyn_free (ht);
  teardown (n, objs);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashdyn * ht = tommy_hashdyn_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      unsigned key = python_hash (objs [i] -> skey);
      if (tommy_hashdyn_search (ht, cmp_str, objs [i], key))
	tommy_hashdyn_remove (ht, cmp_str, objs [i], key);
      else
	tommy_hashdyn_insert (ht, & objs [i] -> _reserved_, objs [i], key);
    }

  count = tommy_hashdyn_count (ht);

  tommy_hashdyn_free (ht);
  teardown (n, objs);

  return count;
}
