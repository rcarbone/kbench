
unsigned grow_int (unsigned n, unsigned * keys)
{
  obj_t * objs = objs_unsigned (keys, n);
  obj_t ** ht = calloc (HASHSIZE, sizeof (* ht));
  unsigned i;
  unsigned count;

  sglib_hashed_obj_t_init (ht);

  for (i = 0; i < n; i ++)
    sglib_hashed_obj_t_add (ht, & objs [i]);

  count = sglib_hashed_obj_t_size (ht);

  free (ht);
  free (objs);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  obj_t * objs = objs_str (keys, n);
  obj_t ** ht = calloc (HASHSIZE, sizeof (* ht));
  unsigned i;
  unsigned count;

  sglib_hashed_obj_t_init (ht);

  for (i = 0; i < n; i ++)
    sglib_hashed_obj_t_add (ht, & objs [i]);

  count = sglib_hashed_obj_t_size (ht);

  free (ht);
  free (objs);

  return count;
}
