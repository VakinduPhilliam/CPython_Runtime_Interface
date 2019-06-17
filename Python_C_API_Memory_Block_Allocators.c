/************************************************ Python C API ************************************************/
/*
  Indeed, it is required to use the same memory API family for a given memory block, so that the risk of mixing different allocators is reduced to a minimum.
  The following code sequence contains two errors, one of which is labeled as fatal because it mixes two different allocators operating on different heaps.
*/ 

char *buf1 = PyMem_New(char, BUFSIZ);
char *buf2 = (char *) malloc(BUFSIZ);

char *buf3 = (char *) PyMem_Malloc(BUFSIZ);

//  ...

PyMem_Del(buf3);  /* Wrong -- should be PyMem_Free() */

free(buf2);       /* Right -- allocated via malloc() */

free(buf1);       /* Fatal -- should be PyMem_Del()  */
