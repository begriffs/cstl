#ifndef C_ERRORS_H
#define C_ERRORS_H

typedef enum clib_error {
/* ------------------------------------------------------------------------*/
/*                 C O M M O N    E R R O R    C O D E                     */
/* ------------------------------------------------------------------------*/
    CLIB_ERROR_SUCCESS,
    CLIB_ERROR_ERROR,
    CLIB_ERROR_MEMORY,
    CLIB_ELEMENT_RETURN_ERROR,

/* ------------------------------------------------------------------------*/
/*         D Y N A M I C    A R R A Y   E R R O R    C O D E S             */
/* ------------------------------------------------------------------------*/
    CLIB_ARRAY_NOT_INITIALIZED = 101,
    CLIB_ARRAY_INDEX_OUT_OF_BOUND,
    CLIB_ARRAY_INSERT_FAILED,

    CLIB_DEQUE_NOT_INITIALIZED = 201,
    CLIB_DEQUE_INDEX_OUT_OF_BOUND,

    CLIB_RBTREE_NOT_INITIALIZED = 301,
    CLIB_RBTREE_KEY_DUPLICATE,
    CLIB_RBTREE_KEY_NOT_FOUND,

    CLIB_SET_NOT_INITIALIZED = 401,
    CLIB_SET_INVALID_INPUT,

    CLIB_MAP_NOT_INITIALIZED = 501,
    CLIB_MAP_INVALID_INPUT,

    CLIB_SLIST_INSERT_FAILED = 601
} clib_error;

#endif
