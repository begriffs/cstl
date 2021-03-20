/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
 *  This file is part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/

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
