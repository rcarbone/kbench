
unsigned udb_int (unsigned n, unsigned * keys)
{
  htab_t ht = htab_create (0, hash_int_fn, eq_int_fn, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (htab_find (ht, & keys [i]))
	htab_remove_elt (ht, (void *) & keys [i]);
      else
	{
	  void ** elem = htab_find_slot (ht, & keys [i], INSERT);
	  if (elem)
	    * elem = (void *) & keys [i];
	}
    }

  count = htab_elements (ht);

  htab_delete (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  htab_t ht = htab_create (0, hash_str_fn, eq_str_fn, NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (htab_find (ht, keys [i]))
	htab_remove_elt (ht, keys [i]);
      else
	{
	  void ** elem = htab_find_slot (ht, keys [i], INSERT);
	  if (elem)
	    * elem = (void *) keys [i];
	}
    }

  count = htab_elements (ht);

  htab_delete (ht);

  return count;
}
