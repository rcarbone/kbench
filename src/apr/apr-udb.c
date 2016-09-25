
unsigned udb_int (unsigned n, unsigned * keys)
{
  apr_hash_t * ht = apr_hash_make (NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, & keys [i], sizeof (keys [i])))
	apr_hash_del (ht, & keys [i], sizeof (keys [i]));
      else
	apr_hash_set (ht, & keys [i], sizeof (keys [i]), & keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_done (ht);

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  apr_hash_t * ht = apr_hash_make (NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, keys [i], strlen (keys [i])))
	apr_hash_del (ht, keys [i], strlen (keys [i]));
      else
	apr_hash_set (ht, keys [i], strlen (keys [i]), keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_done (ht);

  return count;
}
