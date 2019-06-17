/************************************************ Python C API ************************************************/
/*
 Avoiding Memory Corruption.
 Rewritten so that the I/O buffer is allocated from the Python heap by using the first function set:
*/ 

PyObject *res;
char *buf = (char *) PyMem_Malloc(BUFSIZ); /* for I/O */

if (buf == NULL)
    return PyErr_NoMemory();

/* ...Do some I/O operation involving buf... */

res = PyBytes_FromString(buf);
PyMem_Free(buf); /* allocated with PyMem_Malloc */

return res;

/* The same code using the type-oriented function set: */
 
PyObject *res;
char *buf = PyMem_New(char, BUFSIZ); /* for I/O */

if (buf == NULL)
    return PyErr_NoMemory();

/* ...Do some I/O operation involving buf... */

res = PyBytes_FromString(buf);

PyMem_Del(buf); /* allocated with PyMem_New */

return res;
