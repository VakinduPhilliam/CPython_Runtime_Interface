/************************************************* Python C API **********************************************/
/*
  Complex arrays:
  NumPy-style: shape and strides.
  The logical structure of NumPy-style arrays is defined by itemsize, ndim, shape and strides.
  If ndim == 0, the memory location pointed to by buf is interpreted as a scalar of size itemsize. In that case, both shape and strides are NULL.
  If strides is NULL, the array is interpreted as a standard n-dimensional C-array.
  Otherwise, the consumer must access an n-dimensional array as follows:
*/
 
ptr = (char *)buf + indices[0] * strides[0] + ... + indices[n-1] * strides[n-1] item = *((typeof(item) *)ptr);

/*
  'buf' can point to any location within the actual memory block.
  An exporter can check the validity of a buffer with this function:
*/ 

/*

def verify_structure(memlen, itemsize, ndim, shape, strides, offset):

    """Verify that the parameters represent a valid array within
       the bounds of the allocated memory:
           char *mem: start of the physical memory block
           memlen: length of the physical memory block
           offset: (char *)buf - mem
    """

    if offset % itemsize:
        return False

    if offset < 0 or offset+itemsize > memlen:
        return False

    if any(v % itemsize for v in strides):
        return False

    if ndim <= 0:
        return ndim == 0 and not shape and not strides

    if 0 in shape:
        return True

    imin = sum(strides[j]*(shape[j]-1) for j in range(ndim)
               if strides[j] <= 0)

    imax = sum(strides[j]*(shape[j]-1) for j in range(ndim)
               if strides[j] > 0)

    return 0 <= offset+imin and offset+imax+itemsize <= memlen

*/
