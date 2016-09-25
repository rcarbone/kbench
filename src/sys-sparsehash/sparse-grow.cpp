
unsigned grow_int (unsigned n, unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  ht -> set_deleted_key (0xfffffffe);

  for (i = 0; i < n; i ++)
    ht -> insert (hashtable_int_t::value_type (keys [i], keys [i]));

  count = ht -> size ();

  delete ht;

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  hashtable_str_t * ht = new hashtable_str_t;
  unsigned i;
  unsigned count;

  ht -> set_deleted_key ("");

  for (i = 0; i < n; i ++)
    ht -> insert (hashtable_str_t::value_type (keys [i], i));

  count = ht -> size ();

  delete ht;

  return count;
}
