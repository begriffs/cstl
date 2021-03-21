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

#ifndef C_DEQUE_H
#define C_DEQUE_H

struct clib_deque {
    struct clib_object**pElements;
    size_t no_max_elements;
    size_t head;
    size_t tail;
    size_t no_of_elements;
    clib_compare compare_fn;
    clib_destroy destruct_fn;
}c_deque;

struct clib_deque* new_c_deque( size_t deq_size , clib_compare fn_c, clib_destroy fn_d);
clib_error     push_back_c_deque (struct clib_deque* pDeq, void* elem, size_t elem_size);
clib_error     push_front_c_deque(struct clib_deque* pDeq, void* elem,size_t elem_size);

clib_error     front_c_deque     (struct clib_deque* pDeq,void*);
clib_error     back_c_deque      (struct clib_deque* pDeq,void*);
clib_error     pop_back_c_deque  (struct clib_deque* pDeq);
clib_error     pop_front_c_deque (struct clib_deque* pDeq);
clib_bool      empty_c_deque     (struct clib_deque* pDeq);
size_t         size_c_deque ( struct clib_deque* pDeq);
clib_error     delete_c_deque ( struct clib_deque* pDeq);
clib_error     element_at_c_deque (struct clib_deque* pDeq, size_t index, void**elem);

struct clib_iterator* new_iterator_c_deque(struct clib_deque* pDeq);
void delete_iterator_c_deque ( struct clib_iterator* pItr);

#endif
