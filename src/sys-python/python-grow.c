
unsigned grow_int (unsigned n, unsigned * keys)
{
  PyObject * ht;
  unsigned i;
  unsigned count;

  Py_Initialize ();
  ht = PyDict_New ();

  for (i = 0; i < n; i ++)
    PyDict_SetItem (ht, PyLong_FromUnsignedLong (keys [i]), PyLong_FromUnsignedLong (keys [i]));

  count = PyDict_Size (ht);

  PyDict_Clear (ht);
  Py_Finalize ();

  return count;
}


unsigned grow_str (unsigned n, char ** keys)
{
  PyObject * ht;
  unsigned i;
  unsigned count;

  Py_Initialize ();
  ht = PyDict_New ();

  for (i = 0; i < n; i ++)
    PyDict_SetItem (ht, PyString_FromString (keys [i]), PyLong_FromUnsignedLong (i));

  count = PyDict_Size (ht);

  PyDict_Clear (ht);
  Py_Finalize ();

  return count;
}
