#ifndef C_MAP_H
#define C_MAP_H

struct clib_map {
    struct clib_rb* root;
};


struct clib_map* new_c_map    ( clib_compare fn_c_k, clib_destroy fn_k_d, clib_destroy fn_v_d);
clib_error   insert_c_map ( struct clib_map* pMap, void* key, size_t key_size, void* value,  size_t value_size);
clib_bool    exists_c_map ( struct clib_map* pMap, void* key);
clib_error   remove_c_map ( struct clib_map* pMap, void* key);
clib_bool    find_c_map   ( struct clib_map* pMap, void* key, void**value);
clib_error   delete_c_map ( struct clib_map* pMap);

struct clib_iterator* new_iterator_c_map(struct clib_map* pMap);
void delete_iterator_c_map ( struct clib_iterator* pItr);


#endif
