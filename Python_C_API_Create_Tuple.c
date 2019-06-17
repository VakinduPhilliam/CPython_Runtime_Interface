/***************************************** Python C API ***************************************/
/*
  The code to create the tuple (1, 2, "three") could look like this (forgetting about error handling for the moment; a better way to code this is shown
  below):
*/

PyObject *t;

t = PyTuple_New(3);

PyTuple_SetItem(t, 0, PyLong_FromLong(1L));
PyTuple_SetItem(t, 1, PyLong_FromLong(2L));

PyTuple_SetItem(t, 2, PyUnicode_FromString("three"));

/*
  Here, PyLong_FromLong() returns a new reference which is immediately stolen by PyTuple_SetItem().
  When you want to keep using an object although the reference to it will be stolen, use Py_INCREF() to grab another reference before calling the
  reference-stealing function.
*/

/*
  The above two blocks of code could be replaced by the following (which also takes care of the error checking):
*/ 

PyObject *tuple, *list;

tuple = Py_BuildValue("(iis)", 1, 2, "three");

list = Py_BuildValue("[iis]", 1, 2, "three");
