
unsigned udb_int (unsigned n, unsigned * keys)
{
  PyObject * ht;
  unsigned i;
  unsigned count;

  Py_Initialize ();
  ht = PyDict_New ();

  for (i = 0; i < n; i ++)
    {
      PyObject * hit = PyDict_GetItem (ht, PyLong_FromUnsignedLong (keys [i]));
      if (hit)
	PyDict_DelItem (ht, PyLong_FromUnsignedLong (keys [i]));
      else
	PyDict_SetItem (ht, PyLong_FromUnsignedLong (keys [i]), PyLong_FromUnsignedLong (keys [i]));
    }

  count = PyDict_Size (ht);

  PyDict_Clear (ht);
  Py_Finalize ();

  return count;
}


unsigned udb_str (unsigned n, char ** keys)
{
  PyObject * ht;
  unsigned i;
  unsigned count;

  Py_Initialize ();
  ht = PyDict_New ();

  for (i = 0; i < n; i ++)
    {
      PyObject * hit = PyDict_GetItem (ht, PyString_FromString (keys [i]));
      if (hit)
	PyDict_DelItem (ht, PyString_FromString (keys [i]));
      else
	PyDict_SetItem (ht, PyString_FromString (keys [i]), PyLong_FromUnsignedLong (i));
    }

  count = PyDict_Size (ht);

  PyDict_Clear (ht);
  Py_Finalize ();

  return count;
}
