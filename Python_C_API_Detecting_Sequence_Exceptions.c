/******************************************** Python C API ***************************************************/
/*
  A simple example of detecting exceptions and passing them on. 
  The following example function shows some error cleanup. 
*/

int
incr_item(PyObject *dict, PyObject *key)
{

    /* Objects all initialized to NULL for Py_XDECREF */

    PyObject *item = NULL, *const_one = NULL, *incremented_item = NULL;
    int rv = -1; /* Return value initialized to -1 (failure) */

    item = PyObject_GetItem(dict, key);

    if (item == NULL) {

        /* Handle KeyError only: */

        if (!PyErr_ExceptionMatches(PyExc_KeyError))
            goto error;

        /* Clear the error and use zero: */

        PyErr_Clear();

        item = PyLong_FromLong(0L);

        if (item == NULL)
            goto error;
    }

    const_one = PyLong_FromLong(1L);

    if (const_one == NULL)
        goto error;

    incremented_item = PyNumber_Add(item, const_one);

    if (incremented_item == NULL)
        goto error;

    if (PyObject_SetItem(dict, key, incremented_item) < 0)
        goto error;

    rv = 0; /* Success */

    /* Continue with cleanup code */

 error:

    /* Cleanup code, shared by success and failure path */

    /* Use Py_XDECREF() to ignore NULL references */

    Py_XDECREF(item);
    Py_XDECREF(const_one);

    Py_XDECREF(incremented_item);

    return rv; /* -1 for error, 0 for success */

}
 
/*
  This example represents an endorsed use of the goto statement in C!
  It illustrates the use of PyErr_ExceptionMatches() and PyErr_Clear() to handle specific exceptions, and the use of Py_XDECREF() to dispose of owned
  references that may be NULL (note the 'X' in the name; Py_DECREF() would crash when confronted with a NULL reference).
  It is important that the variables used to hold owned references are initialized to NULL for this to work; likewise, the proposed return value is
  initialized to -1 (failure) and only set to success after the final call made is successful.
*/
