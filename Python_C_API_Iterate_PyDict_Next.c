/*************************************************** Python C API ********************************************************/
/*
 Iterate Key-value Pairs.
 int PyDict_Next(PyObject *p, Py_ssize_t *ppos, PyObject **pkey, PyObject **pvalue):
 Iterate over all key-value pairs in the dictionary p.
 The Py_ssize_t referred to by ppos must be initialized to 0 prior to the first call to this function to start the iteration; the function returns true
 for each pair in the dictionary, and false once all pairs have been reported.
 The parameters pkey and pvalue should either point to PyObject* variables that will be filled in with each key and value, respectively, or may be NULL.
 Any references returned through them are borrowed. ppos should not be altered during iteration.
 Its value represents offsets within the internal dictionary structure, and since the structure is sparse, the offsets are not consecutive.
*/

/* For example: */
 
PyObject *key, *value;

Py_ssize_t pos = 0;

while (PyDict_Next(self->dict, &pos, &key, &value)) {

    /* do something interesting with the values... */

    //    ...

}
