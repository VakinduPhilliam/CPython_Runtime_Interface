/******************************************* Python C API ***********************************************/
/*
 How do I call an object’s method from C?
 The PyObject_CallMethod() function can be used to call an arbitrary method of an object.
 The parameters are the object, the name of the method to call, a format string like that used with Py_BuildValue(), and the argument values:
*/ 

PyObject *

PyObject_CallMethod(PyObject *object, const char *method_name,
                    const char *arg_format, ...);

/* 
  This works for any object that has methods – whether built-in or user-defined. You are responsible for eventually Py_DECREF()’ing the return value. 
  To call, e.g., a file object’s “seek” method with arguments 10, 0 (assuming the file object pointer is “f”):
*/ 

res = PyObject_CallMethod(f, "seek", "(ii)", 10, 0);

if (res == NULL) {

/*        ... an exception occurred ...    */

}

else {

        Py_DECREF(res);

}

/* 
  Note that since PyObject_CallObject() always wants a tuple for the argument list, to call a function without arguments, pass “()” for the format, and
  to call a function with one argument, surround the argument in parentheses, e.g. “(i)”.
*/