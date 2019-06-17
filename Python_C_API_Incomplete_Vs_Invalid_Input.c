/************************************** Python C API *****************************************/
/* How do I tell “incomplete input” from “invalid input”? */
/* 
 Sometimes you want to emulate the Python interactive interpreter’s behavior, where it gives you a continuation prompt when the input is incomplete
 (e.g. you typed the start of an “if” statement or you didn’t close your parentheses or triple string quotes), but it gives you a syntax error message
 immediately when the input is invalid.
 In Python you can use the codeop module, which approximates the parser’s behavior sufficiently. 
 IDLE uses this, for example.
 The easiest way to do it in C is to call PyRun_InteractiveLoop() (perhaps in a separate thread) and let the Python interpreter handle the input for you.
 You can also set the PyOS_ReadlineFunctionPointer() to point at your custom input function. See Modules/readline.c and Parser/myreadline.c for more hints.
 However sometimes you have to run the embedded Python interpreter in the same thread as your rest application and you can’t allow the
 PyRun_InteractiveLoop() to stop while waiting for user input.
 The one solution then is to call PyParser_ParseString() and test for e.error equal to E_EOF, which means the input is incomplete.
*/


/* Here’s a sample code fragment. */
 

#include <Python.h>
#include <node.h>
#include <errcode.h>
#include <grammar.h>
#include <parsetok.h>
#include <compile.h>

int testcomplete(char *code)

  /* code should end in \n */
  /* return -1 for error, 0 for incomplete, 1 for complete */

{
  node *n;
  perrdetail e;

  n = PyParser_ParseString(code, &_PyParser_Grammar,
                           Py_file_input, &e);
  if (n == NULL) {
    if (e.error == E_EOF)
      return 0;

    return -1;
  }

  PyNode_Free(n);

  return 1;

}
