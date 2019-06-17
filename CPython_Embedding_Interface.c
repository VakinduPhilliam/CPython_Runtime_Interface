/********************************************** CPython Embedding Interface ***********************************************/
/*
  Very High Level Embedding:
  The simplest form of embedding Python is the use of the very high level interface.
  This interface is intended to execute a Python script without needing to interact with the application directly.
  This can for example be used to perform some operation on a file.
*/

#define PY_SSIZE_T_CLEAN
#include <Python.h>

int
main(int argc, char *argv[])
{

wchar_t *program = Py_DecodeLocale(argv[0], NULL);

if (program == NULL) {
fprintf(stderr, "Fatal error: cannot decode argv[0]\n");

exit(1);

}

Py_SetProgramName(program); /* optional but recommended */
Py_Initialize();

PyRun_SimpleString("from time import time,ctime\n"
"print('Today is', ctime(time()))\n");

if (Py_FinalizeEx() < 0) {

exit(120);

}

PyMem_RawFree(program);

return 0;

}
