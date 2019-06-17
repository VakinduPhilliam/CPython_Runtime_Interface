/******************************************************* Python C API **********************************************/
/*********************************************** Typedef Object Structures *****************************************/
/*
  Traverse Function Pointer:
  traverseproc PyTypeObject.tp_traverse: 
  An optional pointer to a traversal function for the garbage collector.
  This is only used if the Py_TPFLAGS_HAVE_GC flag bit is set. More information about Python’s garbage collection scheme can be found in section
  Supporting Cyclic Garbage Collection.
*/

/* 
  The tp_traverse pointer is used by the garbage collector to detect reference cycles.
  A typical implementation of a tp_traverse function simply calls Py_VISIT() on each of the instance’s members that are Python objects.
  For example, this is function local_traverse() from the _thread extension module:
*/ 

static int
local_traverse(localobject *self, visitproc visit, void *arg)
{

    Py_VISIT(self->args);
    Py_VISIT(self->kw);

    Py_VISIT(self->dict);

    return 0;

}

/*
 inquiry PyTypeObject.tp_clear: 
 An optional pointer to a clear function for the garbage collector. This is only used if the Py_TPFLAGS_HAVE_GC flag bit is set.
 The tp_clear member function is used to break reference cycles in cyclic garbage detected by the garbage collector.
 Taken together, all tp_clear functions in the system must combine to break all reference cycles.
 This is subtle, and if in any doubt supply a tp_clear function.
 For example, the tuple type does not implement a tp_clear function, because it’s possible to prove that no reference cycle can be composed entirely
 of tuples.
 Therefore the tp_clear functions of other types must be sufficient to break any cycle containing a tuple.
 This isn’t immediately obvious, and there’s rarely a good reason to avoid implementing tp_clear.
*/
 
/* 
 Implementations of tp_clear should drop the instance’s references to those of its members that may be Python objects, and set its pointers to those
 members to NULL, as in the following example:
*/ 

static int
local_clear(localobject *self)
{
    Py_CLEAR(self->key);
    Py_CLEAR(self->args);
    Py_CLEAR(self->kw);
    Py_CLEAR(self->dict);
    return 0;
}

/*
 descrgetfunc PyTypeObject.tp_descr_get:  
 An optional pointer to a “descriptor get” function.
*/
 
/* The function signature is; */
 
PyObject * tp_descr_get(PyObject *self, PyObject *obj, PyObject *type);
 
/* This field is inherited by subtypes.*/

/*
 descrsetfunc PyTypeObject.tp_descr_set: 
 An optional pointer to a function for setting and deleting a descriptor’s value.
*/
 
/* The function signature is; */
 
int tp_descr_set(PyObject *self, PyObject *obj, PyObject *value);

/*
  Py_ssize_t PyTypeObject.tp_dictoffset: 
  If the instances of this type have a dictionary containing instance variables, this field is non-zero and contains the offset in the instances of the
  type of the instance variable dictionary; this offset is used by PyObject_GenericGetAttr().
*/

/* The real dictionary offset in an instance can be computed in Python from a negative tp_dictoffset as follows: */
/*

dictoffset = tp_basicsize + abs(ob_size)*tp_itemsize + tp_dictoffset
if dictoffset is not aligned on sizeof(void*):
 
       round up to sizeof(void*)

*/

/* where tp_basicsize, tp_itemsize and tp_dictoffset are taken from the type object, and ob_size is taken from the instance. */

/*
  initproc PyTypeObject.tp_init 
  An optional pointer to an instance initialization function.
*/
 
/* This function corresponds to the __init__() method of classes. Like __init__(), it is possible to create an instance without calling __init__(), and it
 is possible to reinitialize an instance by calling its __init__() method again.
*/
 
/* The function signature is; */
 
/*

int tp_init(PyObject *self, PyObject *args, PyObject *kwds)


*/

/*
destructor PyTypeObject.tp_free: 
An optional pointer to an instance deallocation function. Its signature is freefunc:
*/

/* 

void tp_free(void *)

*/

/*
  allocfunc PyTypeObject.tp_alloc 
  An optional pointer to an instance allocation function.
*/
 
/* The function signature is; */
 
/*

PyObject *tp_alloc(PyTypeObject *self, Py_ssize_t nitems)

*/ 

/*
 inquiry PyTypeObject.tp_is_gc: 
 An optional pointer to a function called by the garbage collector.
*/

/* 
 The garbage collector needs to know whether a particular object is collectible or not.
 Normally, it is sufficient to look at the object’s type’s tp_flags field, and check the Py_TPFLAGS_HAVE_GC flag bit.
 But some types have a mixture of statically and dynamically allocated instances, and the statically allocated instances are not collectible.
 Such types should define this function; it should return 1 for a collectible instance, and 0 for a non-collectible instance.
 The signature is;
*/

/* 

int tp_is_gc(PyObject *self)

*/


/*
  void tp_finalize(PyObject *):
  If tp_finalize is set, the interpreter calls it once when finalizing an instance.
  It is called either from the garbage collector (if the instance is part of an isolated reference cycle) or just before the object is deallocated.
  Either way, it is guaranteed to be called before attempting to break reference cycles, ensuring that it finds the object in a sane state.
  tp_finalize should not mutate the current exception status; therefore, a recommended way to write a non-trivial finalizer is:
*/ 

static void
local_finalize(PyObject *self)
{
    PyObject *error_type, *error_value, *error_traceback;

    /* Save the current exception, if any. */

    PyErr_Fetch(&error_type, &error_value, &error_traceback);

    /* ... */

    /* Restore the saved exception. */

    PyErr_Restore(error_type, error_value, error_traceback);
}
