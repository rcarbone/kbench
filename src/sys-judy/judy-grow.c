
unsigned grow_int (unsigned n, unsigned * keys)
{
  Pvoid_t ht = NULL;
  unsigned i;
  Word_t r;
  Word_t count;

  for (i = 0; i < n; i ++)
    {
      Word_t * p;
      JLG (p, ht, keys [i]);
      JLI (p, ht, keys [i]);
      * p = i;
    }

  JLC (count, ht, 0, -1);

  JLFA (r, ht);

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  Pvoid_t ht = NULL;
  unsigned i;
  Word_t r;
  Word_t count;

  for (i = 0; i < n; i ++)
    {
      Word_t * p;
      JSLG (p, ht, (char *) keys [i]);
      JSLI (p, ht, keys [i]);
      * p = i;
    }

  JLC (count, ht, 0, -1);

  JSLFA (r, ht);

  return count;
}
