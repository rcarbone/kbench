
unsigned grow_int (unsigned n, unsigned * keys)
{
  PerlInterpreter * my_perl = perl_alloc ();
  HV * ht;
  unsigned i;
  unsigned count;

  perl_construct (my_perl);
  ht = newHV ();

  for (i = 0; i < n; i ++)
    {
      SV * key = newSViv (keys [i]);
      SV * val = newSViv (keys [i]);
      hv_store_ent (ht, key, val, 0);
    }

  count = HvKEYS (ht);

  hv_clear (ht);
  perl_destruct (my_perl);
  perl_free (my_perl);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  PerlInterpreter * my_perl = perl_alloc ();
  HV * ht = newHV ();
  unsigned i;
  unsigned count;

  perl_construct (my_perl);

  for (i = 0; i < n; i ++)
    {
      SV * val = newSViv (i);
      hv_store (ht, keys [i], strlen (keys [i]), val, 0);
    }

  count = HvKEYS (ht);

  hv_clear (ht);
  perl_destruct (my_perl);
  perl_free (my_perl);

  return count;
}
