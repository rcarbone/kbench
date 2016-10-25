
unsigned udb_int (unsigned n, unsigned * keys)
{
  obj_t ** objs = setup_int_objs (n, keys);
  tommy_hashtable * ht = tommy_hashtable_alloc (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      unsigned key = java_hash (objs [i] -> ukey);
      if (tommy_hashtable_search (ht, cmp_int, objs [i], key))
	tommy_hashtable_remove (ht, cmp_int, objs [i], key);
      else
	tommy_hashtable_insert (ht, & objs [i] -> _reserved_, objs [i], key);
    }

  count = tommy_hashtable_count (ht);

  tommy_hashtable_free (ht);
  teardown (n, objs);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  obj_t ** objs = setup_str_objs (n, keys);
  tommy_hashtable * ht = tommy_hashtable_alloc (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      unsigned key = python_hash (objs [i] -> skey);
      if (tommy_hashtable_search (ht, cmp_str, objs [i], key))
	tommy_hashtable_remove (ht, cmp_str, objs [i], key);
      else
	tommy_hashtable_insert (ht, & objs [i] -> _reserved_, objs [i], key);
    }

  count = tommy_hashtable_count (ht);

  tommy_hashtable_free (ht);
  teardown (n, objs);

  return count;
}
