
unsigned grow_int (unsigned n, unsigned * keys)
{
  obj_t ** objs = setup_int_objs (n, keys);
  tommy_hashdyn * ht = tommy_hashdyn_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    tommy_hashdyn_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_inthash_u32 (objs [i] -> ukey));

  count = tommy_hashdyn_count (ht);

  tommy_hashdyn_free (ht);
  teardown (n, objs);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashdyn * ht = tommy_hashdyn_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    tommy_hashdyn_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey)));

  count = tommy_hashdyn_count (ht);

  tommy_hashdyn_free (ht);
  teardown (n, objs);

  return count;
}
