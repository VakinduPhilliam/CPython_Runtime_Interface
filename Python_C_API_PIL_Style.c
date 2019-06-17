/*************************************************** Python C API *******************************************/
/*
  PIL-style: shape, strides and suboffsets:
  In addition to the regular items, PIL-style arrays can contain pointers that must be followed in order to get to the next element in a dimension.
  For example, the regular three-dimensional C-array char v[2][2][3] can also be viewed as an array of 2 pointers to 2 two-dimensional arrays: 
  char (*v[2])[2][3].
  In suboffsets representation, those two pointers can be embedded at the start of buf, pointing to two char x[2][3] arrays that can be located anywhere in
  memory.
*/

/* 
  Here is a function that returns a pointer to the element in an N-D array pointed to by an N-dimensional index when there are both non-NULL strides and
  suboffsets:
*/ 

void *get_item_pointer(int ndim, void *buf, Py_ssize_t *strides,
                       Py_ssize_t *suboffsets, Py_ssize_t *indices) {

    char *pointer = (char*)buf;
    int i;

    for (i = 0; i < ndim; i++) {
        pointer += strides[i] * indices[i];

        if (suboffsets[i] >=0 ) {

            pointer = *((char**)pointer) + suboffsets[i];

        }
    }

    return (void*)pointer;

}
