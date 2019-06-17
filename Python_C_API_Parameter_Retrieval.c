/**************************************** Python C API ****************************************/
/*
 int PyArg_UnpackTuple(PyObject *args, const char *name, Py_ssize_t min, Py_ssize_t max, ...).
 A simpler form of parameter retrieval which does not use a format string to specify the types of the arguments.
 Functions which use this method to retrieve their parameters should be declared as METH_VARARGS in function or method tables.
 The tuple containing the actual parameters should be passed as args; it must actually be a tuple.
 The length of the tuple must be at least min and no more than max; min and max may be equal.
 Additional arguments must be passed to the function, each of which should be a pointer to a PyObject* variable; these will be filled in with the values
 from args; they will contain borrowed references.
 The variables which correspond to optional parameters not given by args will not be filled in; these should be initialized by the caller.
 This function returns true on success and false if args is not a tuple or contains the wrong number of elements; an exception will be set if there was a
 failure.
*/ 

/* This is an example of the use of this function, taken from the sources for the _weakref helper module for weak references: */
 
static PyObject *
weakref_ref(PyObject *self, PyObject *args)
{

    PyObject *object;
    PyObject *callback = NULL;

    PyObject *result = NULL;

    if (PyArg_UnpackTuple(args, "ref", 1, 2, &object, &callback)) {

        result = PyWeakref_NewRef(object, callback);

    }

    return result;

}

/* The call to PyArg_UnpackTuple() in this example is entirely equivalent to this call to PyArg_ParseTuple(): */
 
PyArg_ParseTuple(args, "O|O:ref", &object, &callback)
