/****************************** Python C API ***********************************/
/*
 How to access a module written in Python from C.
 You can get a pointer to the module object as follows:
*/ 

module = PyImport_ImportModule("<modulename>");
 
/*
 If the module hasn’t been imported yet (i.e. it is not yet present in sys.modules), this initializes the module; otherwise it simply returns the value of
 sys.modules["<modulename>"].
 Note that it doesn’t enter the module into any namespace – it only ensures it has been initialized and is stored in sys.modules.
 You can then access the module’s attributes (i.e. any name defined in the module) as follows:
*/ 

attr = PyObject_GetAttrString(module, "<attrname>");
 
/*
 Calling PyObject_SetAttrString() to assign to variables in the module also works.
*/