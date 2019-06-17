/********************************************** CPython Runtime Interface ***********************************************/
/* Calling Python Functions from C. */
/*
  Calling a Python function is easy. First, the Python program must somehow pass you the Python function object. 
  You should provide a function (or some other interface) to do this. 
  When this function is called, save a pointer to the Python function object (be careful to Py_INCREF() it!) in a global
  variable — or wherever you see fit.
  For example, the following function might be part of a module definition:
*/

static PyObject *my_callback = NULL;
static PyObject *

my_set_callback(PyObject *dummy, PyObject *args)
{

PyObject *result = NULL;
PyObject *temp;

if (PyArg_ParseTuple(args, "O:set_callback", &temp)) {
if (!PyCallable_Check(temp)) {

PyErr_SetString(PyExc_TypeError, "parameter must be callable");

return NULL;

}

Py_XINCREF(temp); /* Add a reference to new callback */
Py_XDECREF(my_callback); /* Dispose of previous callback */

my_callback = temp; /* Remember new callback */

/* Boilerplate to return "None" */

Py_INCREF(Py_None);

result = Py_None;

}

return result;

}

/*
  To call the Python function with no arguments, pass in NULL, or an empty tuple; to call it with one argument, pass a singleton tuple.
  Py_BuildValue() returns a tuple when its format string consists of zero or more format codes between parentheses.
*/

/* For example: */

int arg;

PyObject *arglist;
PyObject *result;

//...

arg = 123;

//...

/* Time to call the callback */

arglist = Py_BuildValue("(i)", arg);
result = PyObject_CallObject(my_callback, arglist);

Py_DECREF(arglist);

/*
  In some cases the argument list is also provided by the Python program, through the same interface that specified the callback function.
 It can then be saved and used in the same manner as the function object.
 In other cases, you may have to construct a new tuple to pass as the argument list. The simplest way to do this is to call Py_BuildValue().
 For example, if you want to pass an integral event code, you might use the following code:
*/

PyObject *arglist;

// ...

arglist = Py_BuildValue("(l)", eventcode);
result = PyObject_CallObject(my_callback, arglist);

Py_DECREF(arglist);

if (result == NULL)

return NULL; /* Pass error back */

/* Here maybe use the result */

Py_DECREF(result);

/*
  You may also call a function with keyword arguments by using PyObject_Call(), which supports arguments and keyword arguments.
  As in the above example, we use Py_BuildValue() to construct the dictionary.
*/

PyObject *dict;

// ...

dict = Py_BuildValue("{s:i}", "name", val);

result = PyObject_Call(my_callback, NULL, dict);

Py_DECREF(dict);

if (result == NULL)

return NULL; /* Pass error back */

/* Here maybe use the result */

Py_DECREF(result);
