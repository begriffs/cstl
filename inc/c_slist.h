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
