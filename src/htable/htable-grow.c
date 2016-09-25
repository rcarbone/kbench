
unsigned grow_int (unsigned n, unsigned * keys)
{
  item_t * items = calloc (n, sizeof (item_t));
  struct hash_table * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  hash_table_init (ht, INITIAL_SIZE, cmp_int);

  for (i = 0; i < n; i ++)
    items [i] . uval = i;

  for (i = 0; i < n; i ++)
    hash_table_insert (ht, & items [i] . _reserved_, (void *) & keys [i], sizeof (keys [i]));

  count = ht -> num_elems;

  for (i = 0; i < n; i ++)
    {
      struct hash_entry * hit = hash_table_lookup_key (ht, (void *) & keys [i], sizeof (keys [i]));
      if (hit)
	{
	  hash_table_del_entry (ht, hit);
	  hash_entry_finit (hit);
	}
    }

  hash_table_finit (ht);
  free (ht);
  free (items);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  item_t * items = calloc (n, sizeof (item_t));
  struct hash_table * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  hash_table_init (ht, INITIAL_SIZE, NULL);    /* Warning: cmp function set to NULL is mandatory in order to work with strings */

  for (i = 0; i < n; i ++)
    hash_table_insert (ht, & items [i] . _reserved_, keys [i], strlen (keys [i]));

  count = ht -> num_elems;

  /* Cleanup */
  for (i = 0; i < n; i ++)
    {
      struct hash_entry * hit = hash_table_lookup_key (ht, keys [i], strlen (keys [i]));
      if (hit)
	{
	  hash_table_del_entry (ht, hit);
	  hash_entry_finit (hit);
	}
    }

  hash_table_finit (ht);
  free (ht);
  free (items);

  return count;
}
