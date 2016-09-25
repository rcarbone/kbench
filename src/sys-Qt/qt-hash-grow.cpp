
unsigned grow_int (unsigned n, unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    ht -> insert (keys [i], keys [i]);

  count = ht -> size ();

  delete ht;

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  hashtable_str_t * ht = new hashtable_str_t;
  unsigned i;
  unsigned count;

  for (i = 0; i < n; i ++)
    {
      mystr_t p;
      hashtable_str_t::const_iterator hit;

      p . str = keys [i];
      ht -> insert (p, i);
    }

  count = ht -> size ();

  delete ht;

  return count;
}
