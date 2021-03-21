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
