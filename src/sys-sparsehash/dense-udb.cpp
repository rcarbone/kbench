
unsigned udb_int (unsigned n, unsigned * keys)
{
  hashtable_int_t * ht = new hashtable_int_t;
  unsigned i;
  unsigned count;

  ht -> set_deleted_key (0xfffffffe);
  ht -> set_empty_key (0xffffffff);

  for (i = 0; i < n; i ++)
    {
      hashtable_int_t::const_iterator hit = ht -> find (keys [i]);
      if (hit != ht -> end ())
	ht -> erase (hit -> first);
      else
	ht -> insert (hashtable_int_t::value_type (keys [i], keys [i]));
    }

  count = ht -> size ();

  delete ht;

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  hashtable_str_t * ht = new hashtable_str_t;
  unsigned i;
  unsigned count;

  ht -> set_deleted_key ("");
  ht -> set_empty_key ("*");

  for (i = 0; i < n; i ++)
    {
      hashtable_str_t::const_iterator hit = ht -> find (keys [i]);
      if (hit != ht -> end ())
	ht -> erase (hit -> first);
      else
	ht -> insert (hashtable_str_t::value_type (keys [i], i));
    }

  count = ht -> size ();

  delete ht;

  return count;
}
