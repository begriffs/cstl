#ifndef C_ARRAY_H
#define C_ARRAY_H

struct clib_array {
    size_t no_max_elements; /* Number of maximum elements array can hold without reallocation */
    size_t no_of_elements;  /* Number of current elements in the array */
    struct clib_object** pElements; /* actual storage area */
    clib_compare compare_fn; /* Compare function pointer*/
    clib_destroy destruct_fn; /* Destructor function pointer*/
};

struct clib_array* new_c_array ( size_t init_size, clib_compare fn_c, clib_destroy fn_d);
clib_error push_back_c_array ( struct clib_array* pArray, void* elem, size_t elem_size);
clib_error element_at_c_array( struct clib_array* pArray, size_t pos, void**e);
clib_error insert_at_c_array ( struct clib_array* pArray, size_t index, void* elem, size_t elem_size);
size_t size_c_array( struct clib_array* pArray);
size_t capacity_c_array( struct clib_array* pArray );
clib_bool  empty_c_array( struct clib_array* pArray);
clib_error reserve_c_array( struct clib_array* pArray, size_t pos);
clib_error front_c_array( struct clib_array* pArray,void* elem);
clib_error back_c_array( struct clib_array* pArray,void* elem);
clib_error remove_from_c_array ( struct clib_array*, size_t pos);
clib_error delete_c_array( struct clib_array* pArray);

struct clib_iterator* new_iterator_c_array(struct clib_array* pArray);
void delete_iterator_c_array ( struct clib_iterator* pItr);

#endif
