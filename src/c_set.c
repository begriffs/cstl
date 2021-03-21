#include "c_lib.h"

#include <stdio.h>

struct clib_set* 
new_c_set ( clib_compare fn_c, clib_destroy fn_d) {

    struct clib_set* pSet = malloc(sizeof *pSet);
    if (!pSet)
        return NULL;

    pSet->root  = new_c_rb (fn_c, fn_d, NULL);
    if (!pSet->root)
        return NULL;

    return pSet;
}
clib_error   
insert_c_set (struct clib_set* pSet, void* key, size_t key_size) {
    if (!pSet)
        return CLIB_SET_NOT_INITIALIZED;

    return insert_c_rb ( pSet->root, key, key_size, NULL, 0);
}
clib_bool    
exists_c_set ( struct clib_set* pSet, void* key) {
    clib_bool found = clib_false;
    struct clib_rb_node* node;

    if (!pSet)
        return clib_false;
    
    node = find_c_rb ( pSet->root, key);
    if ( node ) {
        return clib_true;
    }
    return found;    
}
clib_error   
remove_c_set ( struct clib_set* pSet, void* key) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    struct clib_rb_node* node;
    if (!pSet)
        return CLIB_SET_NOT_INITIALIZED;

    node = remove_c_rb ( pSet->root, key );
    if ( node ) {
        /*free ( node->raw_data.key);
        free ( node );*/
    }
    return rc;
}
clib_bool    
find_c_set ( struct clib_set* pSet, void* key, void* outKey) {
    struct clib_rb_node* node;

    if (!pSet)
        return clib_false;

    node = find_c_rb ( pSet->root, key);
    if ( !node )
        return clib_false;

    get_raw_clib_object ( node->key, outKey );

    return clib_true;

}

clib_error    
delete_c_set ( struct clib_set* x) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    if ( x ){
        rc = delete_c_rb ( x->root );
        free ( x );
    }
    return rc;
}
static struct clib_rb_node *
minimum_c_set( struct clib_set *x ) {
	return minimum_c_rb( x->root, x->root->root);
}

static struct clib_object* 
get_next_c_set( struct clib_iterator* pIterator ) {
	if ( ! pIterator->pCurrentElement ) {
		pIterator->pCurrentElement = minimum_c_set(pIterator->pContainer);
	}else {
		struct clib_set *x = (struct clib_set*)pIterator->pContainer;
		pIterator->pCurrentElement = tree_successor( x->root, pIterator->pCurrentElement);			              
	}
	if ( ! pIterator->pCurrentElement)
		return NULL;

	return ((struct clib_rb_node*)pIterator->pCurrentElement)->key;
}
static void* 
get_value_c_set( void* pObject) {
	void* elem;
	get_raw_clib_object ( pObject, &elem );
	return elem;
}

struct clib_iterator* 
new_iterator_c_set(struct clib_set* pSet) {
	struct clib_iterator *itr = malloc ( sizeof *itr );
	if (!itr)
		return NULL;
	itr->get_next     = get_next_c_set;
	itr->get_value    = get_value_c_set;
	itr->pContainer   = pSet;
	itr->pCurrent     = 0;
	itr->pCurrentElement = NULL;
	return itr;
}
void
delete_iterator_c_set ( struct clib_iterator* pItr) {
	free ( pItr );
}
