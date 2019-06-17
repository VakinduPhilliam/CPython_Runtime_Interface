/******************************************************* Python C API *****************************************************/
/*
  Retrieve Start, Stop and Step Indices.
  int PySlice_GetIndicesEx(PyObject *slice, Py_ssize_t length, Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step, Py_ssize_t *slicelength):
  Usable replacement for PySlice_GetIndices().
  Retrieve the start, stop, and step indices from the slice object slice assuming a sequence of length length, and store the length of the slice in
  slicelength.
  Out of bounds indices are clipped in a manner consistent with the handling of normal slices.
  Returns 0 on success and -1 on error with exception set.
*/ 

/*
  Note:
  This function is considered not safe for resizable sequences.
  Its invocation should be replaced by a combination of PySlice_Unpack() and PySlice_AdjustIndices() where
*/ 

if (PySlice_GetIndicesEx(slice, length, &start, &stop, &step, &slicelength) < 0) {

    // return error

}

/* is replaced by */ 

if (PySlice_Unpack(slice, &start, &stop, &step) < 0) {

    // return error

}

slicelength = PySlice_AdjustIndices(length, &start, &stop, step);
