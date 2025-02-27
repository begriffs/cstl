#include "c_lib.h"

#include <stdio.h>


struct clib_map* 
new_c_map ( clib_compare fn_c_k, clib_destroy fn_k_d,  
            clib_destroy fn_v_d) {

    struct clib_map* pMap = malloc(sizeof *pMap);
    if (!pMap)
        return NULL;

    pMap->root  = new_c_rb (fn_c_k, fn_k_d, fn_v_d);
    if (!pMap->root)
        return NULL;

    return pMap;
}
clib_error   
insert_c_map ( struct clib_map* pMap, void* key, size_t key_size, void* value,  size_t value_size) {
    if (!pMap)
        return CLIB_MAP_NOT_INITIALIZED;

    return insert_c_rb ( pMap->root, key, key_size, value, value_size);
}
clib_bool    
exists_c_map ( struct clib_map* pMap, void* key) {
    clib_bool found = clib_false;
    struct clib_rb_node* node;

    if (!pMap)
        return clib_false;
    
    node = find_c_rb ( pMap->root, key);
    if ( node ) {
        return clib_true;
    }
    return found;    
}
clib_error   
remove_c_map ( struct clib_map* pMap, void* key) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    struct clib_rb_node* node;
    if (!pMap)
        return CLIB_MAP_NOT_INITIALIZED;

    node = remove_c_rb ( pMap->root, key );
    if ( node ) {
        void* removed_node;
        get_raw_clib_object ( node->key, &removed_node );
        free ( removed_node);
        delete_clib_object ( node->key );

        get_raw_clib_object ( node->value, &removed_node );
        free ( removed_node);
        delete_clib_object ( node->value);

        free ( node );
    }
    return rc;
}
clib_bool    
find_c_map ( struct clib_map* pMap, void* key, void**value) {
    struct clib_rb_node* node;

    if (!pMap)
        return clib_false;

    node = find_c_rb ( pMap->root, key);
    if ( !node )
        return clib_false;

    get_raw_clib_object ( node->value, value );

    return clib_true;

}

clib_error    
delete_c_map ( struct clib_map* x) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    if ( x ){
        rc = delete_c_rb ( x->root );
        free ( x );
    }
    return rc;
}

static struct clib_rb_node *
minimum_c_map( struct clib_map *x ) {
	return minimum_c_rb( x->root, x->root->root);
}

static struct clib_object* 
get_next_c_map( struct clib_iterator* pIterator ) {
	if ( ! pIterator->pCurrentElement ) {
		pIterator->pCurrentElement = minimum_c_map(pIterator->pContainer);
	}else {
		struct clib_map *x = (struct clib_map*)pIterator->pContainer;
		pIterator->pCurrentElement = tree_successor( x->root, pIterator->pCurrentElement);			              
	}
	if ( ! pIterator->pCurrentElement)
		return NULL;

	return ((struct clib_rb_node*)pIterator->pCurrentElement)->value;
}
static void* 
get_value_c_map( void* pObject) {
	void* elem;
	get_raw_clib_object ( pObject, &elem );
	return elem;
}
static void
replace_value_c_map(struct clib_iterator *pIterator, void* elem, size_t elem_size) {
	struct clib_map*  pMap = (struct clib_map*)pIterator->pContainer;
	
	if ( pMap->root->destruct_v_fn ) {
		void* old_element;
		get_raw_clib_object (((struct clib_rb_node*)pIterator->pCurrentElement)->value, &old_element );
		pMap->root->destruct_v_fn(old_element);
    }
	replace_raw_clib_object(((struct clib_rb_node*)pIterator->pCurrentElement)->value, elem, elem_size);
}


struct clib_iterator* 
new_iterator_c_map(struct clib_map* pMap) {
	struct clib_iterator *itr = malloc ( sizeof *itr );
	if (!itr)
		return NULL;
	itr->get_next     = get_next_c_map;
	itr->get_value    = get_value_c_map;
	itr->replace_value = replace_value_c_map;
	itr->pContainer   = pMap;
	itr->pCurrent     = 0;
	itr->pCurrentElement = NULL;
	return itr;
}
void
delete_iterator_c_map ( struct clib_iterator* pItr) {
	free ( pItr );
}
