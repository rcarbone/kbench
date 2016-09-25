
unsigned grow_int (unsigned n, unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  ht -> init ();

  for (i = 0; i < n; i ++)
    {
      hashtable_int_t::Insert hit = ht -> findForAdd (keys [i]);
      ht -> add (hit, keys [i], i + 1);
    }

  count = ht -> elements ();

  delete ht;

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  hashtable_str_t * ht = new hashtable_str_t;
  unsigned i;
  unsigned count;

  ht -> init ();

  for (i = 0; i < n; i ++)
    {
      hashtable_str_t::Insert hit = ht -> findForAdd (keys [i]);
      if (hit . found ())
	ht -> remove (hit);
      else
	ht -> add (hit, AString (keys [i]), i);
    }

  count = ht -> elements ();

  delete ht;

  return count;
}
