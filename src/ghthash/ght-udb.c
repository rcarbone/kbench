
unsigned udb_int (unsigned n, unsigned * keys)
{
  ght_hash_table_t * ht = ght_create (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (ght_get (ht, sizeof (keys [i]), & keys [i]))
	ght_remove (ht, sizeof (keys [i]), & keys [i]);
      else
	ght_insert (ht, (void *) & keys [i], sizeof (keys [i]), & keys [i]);
    }

  count = ght_count (ht);

  ght_finalize (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  ght_hash_table_t * ht = ght_create (n);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (ght_get (ht, strlen (keys [i]), keys [i]))
	ght_remove (ht, strlen (keys [i]), keys [i]);
      else
	ght_insert (ht, (void *) keys [i], strlen (keys [i]), keys [i]);
    }

  count = ght_count (ht);

  ght_finalize (ht);

  return count;
}
