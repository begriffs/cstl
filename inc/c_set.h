#ifndef C_SET_H
#define C_SET_H

struct clib_set {
    struct clib_rb* root;
};

struct clib_set* new_c_set( clib_compare fn_c, clib_destroy fn_d);
clib_error   insert_c_set ( struct clib_set* pSet, void* key, size_t key_size);
clib_bool    exists_c_set ( struct clib_set* pSet, void* key);
clib_error   remove_c_set ( struct clib_set* pSet, void* key);
clib_bool    find_c_set   ( struct clib_set* pSet, void* key, void* outKey);
clib_error   delete_c_set ( struct clib_set* pSet);

struct clib_iterator* new_iterator_c_set(struct clib_set* pSet);
void delete_iterator_c_set ( struct clib_iterator* pItr);

#endif
