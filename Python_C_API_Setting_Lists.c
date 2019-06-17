/************************************** Python C API ************************************/
/* This function sets all items of a list (actually, any mutable sequence) to a given item: */
 
int
set_all(PyObject *target, PyObject *item)
{
    Py_ssize_t i, n;

    n = PyObject_Length(target);

    if (n < 0)

        return -1;

    for (i = 0; i < n; i++) {

        PyObject *index = PyLong_FromSsize_t(i);

        if (!index)
            return -1;

        if (PyObject_SetItem(target, index, item) < 0) {
            Py_DECREF(index);

            return -1;

        }

        Py_DECREF(index);

    }

    return 0;

}
