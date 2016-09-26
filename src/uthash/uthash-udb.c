
unsigned udb_int (unsigned n, unsigned * keys)
{
  ht_t * items = calloc (n, sizeof (ht_t));
  ht_t * ht = NULL;                            /* important! initialize to NULL */
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      items [i] . key = keys [i];
      items [i] . val = i;
    }

  for (i = 0; i < n; i ++)
    {
      ht_t * hit;
      HASH_FIND_INT (ht, & keys [i], hit);
      if (hit)
	HASH_DEL (ht, hit);
      else
	HASH_ADD_INT (ht, key, & items [i]);
    }

  count = HASH_COUNT (ht);

  HASH_CLEAR (hh, ht);
  free (items);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  ht_t * items = calloc (n, sizeof (ht_t));
  ht_t * ht = NULL;                            /* important! initialize to NULL */
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      strcpy (items [i] . str, keys [i]);
      items [i] . key = i;
    }

  for (i = 0; i < n; i ++)
    {
      ht_t * hit;
      HASH_FIND_STR (ht, keys [i], hit);
      if (hit)
	HASH_DEL (ht, hit);
      else
	HASH_ADD_KEYPTR (hh, ht, items [i] . str, strlen (items [i] . str), & items [i]);
    }

  count = HASH_COUNT (ht);

  HASH_CLEAR (hh, ht);
  free (items);

  return count;
}
