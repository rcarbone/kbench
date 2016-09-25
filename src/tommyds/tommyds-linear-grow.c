
unsigned grow_int (unsigned n, unsigned * keys)
{
  obj_t ** objs = setup_int_objs (n, keys);
  tommy_hashlin * ht = tommy_hashlin_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    tommy_hashlin_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_inthash_u64 (objs [i] -> ukey));

  count = tommy_hashlin_count (ht);

  tommy_hashlin_free (ht);
  teardown (n, objs);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashlin * ht = tommy_hashlin_alloc ();
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    tommy_hashlin_insert (ht, & objs [i] -> _reserved_, objs [i], tommy_hash_u64 (0, objs [i] -> skey, strlen (objs [i] -> skey)));

  count = tommy_hashlin_count (ht);

  tommy_hashlin_free (ht);
  teardown (n, objs);

  return count;
}
