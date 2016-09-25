
unsigned udb_int (unsigned n, unsigned * keys)
{
  apr_pool_t * p;
  apr_hash_t * ht;
  unsigned i;
  unsigned count;

  apr_pool_initialize ();
  apr_pool_create (& p, NULL);

  ht = apr_hash_make (p);

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, & keys [i], sizeof (keys [i])))
	apr_hash_del (ht, & keys [i], sizeof (keys [i]));
      else
	apr_hash_set (ht, & keys [i], sizeof (keys [i]), & keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_clear (ht);
  apr_pool_destroy (p);
  apr_pool_terminate ();

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  apr_pool_t * p;
  apr_hash_t * ht;
  unsigned i;
  unsigned count;

  apr_pool_initialize ();
  apr_pool_create (& p, NULL);

  ht = apr_hash_make (p);

  for (i = 0; i < n; i ++)
    {
      if (apr_hash_get (ht, keys [i], strlen (keys [i])))
	apr_hash_del (ht, keys [i], strlen (keys [i]));
      else
	apr_hash_set (ht, keys [i], strlen (keys [i]), keys [i]);
    }

  count = apr_hash_count (ht);

  apr_hash_clear (ht);
  apr_pool_destroy (p);
  apr_pool_terminate ();

  return count;
}
