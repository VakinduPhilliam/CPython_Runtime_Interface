/******************************************** Python C API ******************************************/
/*
  Async Object Structures:
  PyAsyncMethods; 
  This structure holds pointers to the functions required to implement awaitable and asynchronous iterator objects.
*/
 
/* Here is the structure definition: */
 
typedef struct {

    unaryfunc am_await;
    unaryfunc am_aiter;
    unaryfunc am_anext;

} PyAsyncMethods;

/*
  unaryfunc PyAsyncMethods.am_await 
*/

/* The signature of this function is: */
 

/* PyObject *am_await(PyObject *self) */
 
/*
  The returned object must be an iterator, i.e. PyIter_Check() must return 1 for it.
  This slot may be set to NULL if an object is not an awaitable.
*/

  unaryfunc PyAsyncMethods.am_aiter;

/* The signature of this function is: */
 
/* PyObject *am_aiter(PyObject *self) */
 
/*
  Must return an awaitable object. See __anext__() for details.
  This slot may be set to NULL if an object does not implement asynchronous iteration protocol.
*/

/*
  unaryfunc PyAsyncMethods.am_anext 
*/

/* The signature of this function is: */
 
/* PyObject *am_anext(PyObject *self) */
 
/*
  Must return an awaitable object.
  This slot may be set to NULL.
*/
