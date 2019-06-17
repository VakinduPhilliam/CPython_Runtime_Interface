/*************************************************** Python C API ********************************************************/
/*
  Update or Merge Dictionary:
  int PyDict_MergeFromSeq2(PyObject *a, PyObject *seq2, int override); 
  Update or merge into dictionary a, from the key-value pairs in seq2.
  seq2 must be an iterable object producing iterable objects of length 2, viewed as key-value pairs.
  In case of duplicate keys, the last wins if override is true, else the first wins.
  Return 0 on success or -1 if an exception was raised.
  Equivalent Python (except for the return value):
*/ 

def PyDict_MergeFromSeq2(a, seq2, override):
    for key, value in seq2:

        if override or key not in a:

            a[key] = value
