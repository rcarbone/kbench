
unsigned grow_int (unsigned n, unsigned * keys)
{
  apr_hash_t * ht = apr_hash_make (NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    apr_hash_set (ht, & keys [i], sizeof (keys [i]), & keys [i]);

  count = apr_hash_count (ht);

  apr_hash_done (ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  apr_hash_t * ht = apr_hash_make (NULL);
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    apr_hash_set (ht, keys [i], strlen (keys [i]), keys [i]);

  count = apr_hash_count (ht);

  apr_hash_done (ht);

  return count;
}
