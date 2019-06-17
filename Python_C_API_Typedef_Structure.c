/********************************************* Python C API ***********************************************/
/*
  Python Typedef:
  PyGetSetDef; 
  Structure to define property-like access for a type. 
*/

/* The get function takes one PyObject* parameter (the instance) and a function pointer (the associated closure): */
 
typedef PyObject *(*getter)(PyObject *, void *);

/* 
  It should return a new reference on success or NULL with a set exception on failure.
*/
 
/* set functions take two PyObject* parameters (the instance and the value to be set) and a function pointer (the associated closure):*/

typedef int (*setter)(PyObject *, PyObject *, void *);
