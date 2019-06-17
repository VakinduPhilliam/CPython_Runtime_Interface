/********************************************** CPython Embedding Interface ***********************************************/
/*
 Extending Embedded Python:
 Until now, the embedded Python interpreter had no access to functionality from the application itself.
 The Python API allows this by extending the embedded interpreter.
 That is, the embedded interpreter gets extended with routines provided by the application. While it sounds complex, it is not so bad.
 Simply forget for a while that the application starts the Python interpreter.
 Instead, consider the application to be a set of subroutines, and write some glue code that gives Python access to those routines, just like you would 
 write a normal Python extension.
 For example:
*/

static int numargs=0;


/* Return the number of arguments of the application command line */

static PyObject*
emb_numargs(PyObject *self, PyObject *args)
{

if(!PyArg_ParseTuple(args, ":numargs"))
return NULL;

return PyLong_FromLong(numargs);

}

static PyMethodDef EmbMethods[] = {
{"numargs", emb_numargs, METH_VARARGS,
"Return the number of arguments received by the process."},
{NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {

PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
NULL, NULL, NULL, NULL

};

static PyObject*
PyInit_emb(void)
{

return PyModule_Create(&EmbModule);

}
