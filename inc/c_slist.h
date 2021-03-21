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

#ifndef C_SLIST_H
#define C_SLIST_H

struct clib_slist_node {
    struct clib_object* elem;
    struct clib_slist_node *next;
};


struct clib_slist {
    struct clib_slist_node* head;
    clib_destroy destruct_fn;
    clib_compare compare_key_fn;
    size_t size;
};


struct clib_slist* new_c_slist(clib_destroy fn_d, clib_compare fn_c);
void           delete_c_slist   (struct clib_slist* pSlist);
clib_error     insert_c_slist   (struct clib_slist* pSlist, size_t pos, void* elem, size_t elem_size);
clib_error     push_back_c_slist(struct clib_slist* pSlist, void* elem, size_t elem_size);
void           remove_c_slist   (struct clib_slist* pSlist, size_t pos);
void           for_each_c_slist (struct clib_slist* pSlist, void (*fn)(void* ));
clib_bool      find_c_slist     (struct clib_slist* pSlist, void* find_value, void**out_value);


struct clib_iterator* new_iterator_c_slist(struct clib_slist* pSlit);
void delete_iterator_c_slist ( struct clib_iterator* pItr);


#endif
