/************************************************ Python C API ************************************************/
/*
   To avoid memory corruption, extension writers should never try to operate on Python objects with the functions exported by the C library: malloc(),
   calloc(), realloc() and free().
   This will result in mixed calls between the C allocator and the Python memory manager with fatal consequences, because they implement different
   algorithms and operate on different heaps.
   However, one may safely allocate and release memory blocks with the C library allocator for individual purposes, as shown in the following example:
*/ 

PyObject *res;

char *buf = (char *) malloc(BUFSIZ); /* for I/O */

if (buf == NULL)
    return PyErr_NoMemory();

//  ...Do some I/O operation involving buf...

res = PyBytes_FromString(buf);

free(buf); /* malloc'ed */

return res;
