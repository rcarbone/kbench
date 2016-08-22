#include "benchmark.h"

/* The implementation */
#include <Python.h>

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

int udb_int (int n, const unsigned * keys)
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


int udb_str (int n, char * const * keys)
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


int main (int argc, char * argv [])
{
  return udb_benchmark (argc, argv, udb_int, udb_str);
}
