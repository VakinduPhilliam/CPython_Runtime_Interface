/********************************************** CPython Runtime Interface ***********************************************/
/* Providing a C API for an Extension Module. */
/*
 Many extension modules just provide new functions and types to be used from Python, but sometimes the code in an
 extension module can be useful for other extension modules.
 For example, an extension module could implement a type “collection” which works like lists without order.
 Just like the standard Python list type has a C API which permits extension modules to create and manipulate lists, this new collection type should have
 a set of C functions for direct manipulation from other extension modules.
*/

/*
 The exporting module is a modification of the spam module from section A Simple Example.
 The function spam.system() does not call the C library function system() directly, but a function PySpam_System(), which would of course do something more
 complicated in reality (such as adding “spam” to every command).
 This function PySpam_System() is also exported to other extension modules.
 The function PySpam_System() is a plain C function, declared static like everything else:
*/

static int
PySpam_System(const char *command)

{

return system(command);

}

/* The function spam_system() is modified in a trivial way: */

static PyObject *
spam_system(PyObject *self, PyObject *args)
{

const char *command;
int sts;

if (!PyArg_ParseTuple(args, "s", &command))

return NULL;

sts = PySpam_System(command);

return PyLong_FromLong(sts);

}

/* In the beginning of the module, right after the line.*/

#include <Python.h>

/* two more lines must be added: */

#define SPAM_MODULE
#include "spammodule.h"

/*
  The #define is used to tell the header file that it is being included in the exporting module, not a client module.
  Finally, the module’s initialization function must take care of initializing the C API pointer array:
*/

PyMODINIT_FUNC
PyInit_spam(void)
{

PyObject *m;
static void *PySpam_API[PySpam_API_pointers];

PyObject *c_api_object;

m = PyModule_Create(&spammodule);

if (m == NULL)

return NULL;

/* Initialize the C API pointer array */

PySpam_API[PySpam_System_NUM] = (void *)PySpam_System;

/* Create a Capsule containing the API pointer array's address */

c_api_object = PyCapsule_New((void *)PySpam_API, "spam._C_API", NULL);

if (c_api_object != NULL)
PyModule_AddObject(m, "_C_API", c_api_object);

return m;

}

/*
  Note that PySpam_API is declared static; otherwise the pointer array would disappear when PyInit_spam() terminates!
  The bulk of the work is in the header file spammodule.h, which looks like this:
*/

#ifndef Py_SPAMMODULE_H
#define Py_SPAMMODULE_H
#ifdef __cplusplus

extern "C" {

#endif

/* Header file for spammodule */
/* C API functions */

#define PySpam_System_NUM 0
#define PySpam_System_RETURN int
#define PySpam_System_PROTO (const char *command)

/* Total number of C API pointers */

#define PySpam_API_pointers 1
#ifdef SPAM_MODULE

/* This section is used when compiling spammodule.c */

static PySpam_System_RETURN PySpam_System PySpam_System_PROTO;

#else

/* This section is used in modules that use spammodule's API */

static void **PySpam_API;

#define PySpam_System \
(*(PySpam_System_RETURN (*)PySpam_System_PROTO) PySpam_API[PySpam_System_NUM])

/* Return -1 on error, 0 on success.
* PyCapsule_Import will set an exception if there's an error.
*/

static int
import_spam(void)
{

PySpam_API = (void **)PyCapsule_Import("spam._C_API", 0);

return (PySpam_API != NULL) ? 0 : -1;

}

#endif
#ifdef __cplusplus

}

#endif
#endif /* !defined(Py_SPAMMODULE_H) */

/*
  All that a client module must do in order to have access to the function PySpam_System() is to call the function (or rather macro) import_spam() in its
  initialization function:
*/

PyMODINIT_FUNC

PyInit_client(void)
{

PyObject *m;
m = PyModule_Create(&clientmodule);

if (m == NULL)
return NULL;

if (import_spam() < 0)
return NULL;

/* additional initialization can happen here */

return m;

}
