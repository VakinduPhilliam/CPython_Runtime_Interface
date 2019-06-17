/**************************************************** Python C API **********************************************/
/*
 Number Object Structures:
 PyNumberMethods; 
 This structure holds pointers to the functions which an object uses to implement the number protocol.
 Each function is used by the function of similar name documented in the Number Protocol section.
*/
 
/* Here is the structure definition:*/
 

typedef struct {
     binaryfunc nb_add;
     binaryfunc nb_subtract;

     binaryfunc nb_multiply;
     binaryfunc nb_remainder;
     binaryfunc nb_divmod;

     ternaryfunc nb_power;

     unaryfunc nb_negative;
     unaryfunc nb_positive;
     unaryfunc nb_absolute;

     inquiry nb_bool;
     unaryfunc nb_invert;

     binaryfunc nb_lshift;
     binaryfunc nb_rshift;

     binaryfunc nb_and;
     binaryfunc nb_xor;
     binaryfunc nb_or;

     unaryfunc nb_int;

     void *nb_reserved;

     unaryfunc nb_float;

     binaryfunc nb_inplace_add;
     binaryfunc nb_inplace_subtract;
     binaryfunc nb_inplace_multiply;

     binaryfunc nb_inplace_remainder;

     ternaryfunc nb_inplace_power;

     binaryfunc nb_inplace_lshift;
     binaryfunc nb_inplace_rshift;
     binaryfunc nb_inplace_and;

     binaryfunc nb_inplace_xor;
     binaryfunc nb_inplace_or;

     binaryfunc nb_floor_divide;
     binaryfunc nb_true_divide;

     binaryfunc nb_inplace_floor_divide;
     binaryfunc nb_inplace_true_divide;

     unaryfunc nb_index;

     binaryfunc nb_matrix_multiply;
     binaryfunc nb_inplace_matrix_multiply;

} PyNumberMethods;
