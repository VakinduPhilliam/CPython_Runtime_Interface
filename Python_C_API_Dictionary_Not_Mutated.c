/*************************************************** Python C API ********************************************************/
/*
  The dictionary p should not be mutated during iteration.
  It is safe to modify the values of the keys as you iterate over the dictionary, but only so long as the set of keys does not change.
*/

/* For example: */ 

PyObject *key, *value;
Py_ssize_t pos = 0;

while (PyDict_Next(self->dict, &pos, &key, &value)) {
    long i = PyLong_AsLong(value);

    if (i == -1 && PyErr_Occurred()) {

        return -1;

    }

    PyObject *o = PyLong_FromLong(i + 1);

    if (o == NULL)
        return -1;

    if (PyDict_SetItem(self->dict, key, o) < 0) {
        Py_DECREF(o);

        return -1;

    }

    Py_DECREF(o);

}
