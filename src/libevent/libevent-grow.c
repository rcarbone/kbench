
unsigned grow_int (unsigned n, unsigned * keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  ht_int_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      objs [i] . ukey = keys [i];
      objs [i] . uval = i;
    }

  HT_INIT (evht_int, ht);

  for (i = 0; i < n; i ++)
    {
      HT_INSERT (evht_int, ht, & objs [i]);
    }

  count = HT_SIZE (ht);

  HT_CLEAR (evht_int, ht);
  free (ht);
  free (objs);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  ht_str_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      strcpy (objs [i] . skey, keys [i]);
      objs [i] . uval = i;
    }

  for (i = 0; i < n; i ++)
    {
      HT_INSERT (evht_str, ht, & objs [i]);
    }

  count = HT_SIZE (ht);

  HT_CLEAR (evht_str, ht);
  free (ht);
  free (objs);

  return count;
}
