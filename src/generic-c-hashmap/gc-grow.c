
unsigned grow_int (unsigned n, unsigned * keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  gch_int_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      objs [i] . ukey = keys [i];
      objs [i] . uval = i;
    }

  for (i = 0; i < n; i ++)
    {
      obj_t * obj = & objs [i];
      gch_int_Put (ht, & obj, HMDR_STACK);
    }

  count = ht -> size;

  gch_int_Destroy (ht);
  free (ht);
  free (objs);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  obj_t * objs = calloc (n, sizeof (obj_t));
  gch_str_t * ht = calloc (1, sizeof (* ht));
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      strcpy (objs [i] . skey, keys [i]);
      objs [i] . uval = i;
    }

  for (i = 0; i < n; i ++)
    {
      obj_t * obj = & objs [i];
      gch_str_Put (ht, & obj, HMDR_STACK);
    }

  count = ht -> size;

  gch_str_Destroy (ht);
  free (ht);
  free (objs);

  return count;
}
