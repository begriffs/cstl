#include "c_lib.h"
#include <string.h>
#include <stdio.h>


static struct clib_array* 
array_check_and_grow ( struct clib_array* pArray) {
    if ( pArray->no_of_elements >= pArray->no_max_elements ) {
        pArray->no_max_elements  = 2 * pArray->no_max_elements;
        pArray->pElements        = realloc ( pArray->pElements, 
                                      pArray->no_max_elements * sizeof ( struct clib_object*));
    }
    return pArray;
}

struct clib_array* 
new_c_array(size_t array_size, clib_compare fn_c, clib_destroy fn_d) {

    struct clib_array* pArray = malloc(sizeof *pArray);
    if ( ! pArray )
        return NULL;

    pArray->no_max_elements = array_size < 8 ? 8 : array_size;
    pArray->pElements = malloc(pArray->no_max_elements * sizeof(struct clib_object*));
    if ( ! pArray->pElements ){
        free ( pArray );
        return NULL;
    }
    pArray->compare_fn      = fn_c;
    pArray->destruct_fn     = fn_d;
    pArray->no_of_elements  = 0;

    return pArray;
}

static clib_error 
insert_c_array ( struct clib_array* pArray, size_t index, void* elem, size_t elem_size) {

    clib_error rc           = CLIB_ERROR_SUCCESS;
    struct clib_object* pObject = new_clib_object ( elem, elem_size );
    if ( ! pObject )
        return CLIB_ARRAY_INSERT_FAILED;

    pArray->pElements[index] = pObject;
    pArray->no_of_elements++;
    return rc;
}

clib_error 
push_back_c_array (struct clib_array* pArray, void* elem, size_t elem_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;	

    if ( ! pArray)
        return CLIB_ARRAY_NOT_INITIALIZED;

    array_check_and_grow ( pArray);

    rc = insert_c_array( pArray, pArray->no_of_elements, elem, elem_size);

    return rc;
}

clib_error 
element_at_c_array (struct clib_array* pArray, size_t index, void** elem) {
    clib_error rc = CLIB_ERROR_SUCCESS;

    if ( ! pArray )
        return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index >= pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    get_raw_clib_object ( pArray->pElements[index], elem );
    return rc;
}

size_t
size_c_array ( struct clib_array* pArray ) {
	if ( !pArray )
		return 0;
	return pArray->no_of_elements - 1 ;
}

size_t
capacity_c_array ( struct clib_array* pArray ) {
	if ( !pArray )
		return 0;
	return pArray->no_max_elements;
}

clib_bool  
empty_c_array ( struct clib_array* pArray) {
	if ( !pArray )
		return 0;
	return pArray->no_of_elements == 0 ? clib_true : clib_false;
}

clib_error 
reserve_c_array ( struct clib_array* pArray, size_t new_size) {
	if ( !pArray )
		return CLIB_ARRAY_NOT_INITIALIZED;

	if ( new_size <= pArray->no_max_elements )
		return CLIB_ERROR_SUCCESS;

	array_check_and_grow ( pArray);
	return CLIB_ERROR_SUCCESS;

}

clib_error 
front_c_array ( struct clib_array* pArray,void* elem) {
    return element_at_c_array ( pArray, 0, elem );
}

clib_error 
back_c_array ( struct clib_array* pArray,void* elem) {
    return element_at_c_array ( pArray, pArray->no_of_elements - 1, elem );
}

clib_error 
insert_at_c_array ( struct clib_array* pArray, size_t index, void* elem, size_t elem_size) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    if ( ! pArray )
        return CLIB_ARRAY_NOT_INITIALIZED;

    if ( index < 0 || index >= pArray->no_of_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    array_check_and_grow ( pArray);

    memmove ( &(pArray->pElements[index + 1]),
              &pArray->pElements[index],
              (pArray->no_of_elements - index ) * sizeof(struct clib_object*));

    rc = insert_c_array ( pArray, index, elem , elem_size);

    return rc;
}

clib_error     
remove_from_c_array ( struct clib_array* pArray, size_t index) {
    clib_error   rc = CLIB_ERROR_SUCCESS;

    if ( ! pArray )
        return rc;
    if ( index < 0 || index >= pArray->no_max_elements )
        return CLIB_ARRAY_INDEX_OUT_OF_BOUND;

    if ( pArray->destruct_fn ) {
        void* elem;
        if ( CLIB_ERROR_SUCCESS == element_at_c_array ( pArray, index , &elem ) ) {
            pArray->destruct_fn(elem);
        }
    }
    delete_clib_object ( pArray->pElements[index]);

    memmove ( &(pArray->pElements[index]),
              &pArray->pElements[index + 1],
              (pArray->no_of_elements - index - 1 ) * sizeof(struct clib_object*));
    pArray->no_of_elements--;

    return rc;
}

clib_error 
delete_c_array( struct clib_array* pArray) {
    clib_error rc = CLIB_ERROR_SUCCESS;
    size_t i = 0;

    if ( !pArray )
        return rc;

    if ( pArray->destruct_fn ) {
        for ( i = 0; i < pArray->no_of_elements; i++) {
            void* elem;
            if ( CLIB_ERROR_SUCCESS == element_at_c_array ( pArray, i , &elem ) )
                pArray->destruct_fn(elem);
        }
    }

    for ( i = 0; i < pArray->no_of_elements; i++) 
        delete_clib_object ( pArray->pElements[i]);    

    free ( pArray->pElements);
    free ( pArray );
    return rc;
}

static struct clib_object* 
get_next_c_array( struct clib_iterator* pIterator ) {

	struct clib_array *pArray = (struct clib_array*)pIterator->pContainer;

	if (pIterator->pCurrent > size_c_array (pArray))
		return NULL;

	pIterator->pCurrentElement = pArray->pElements[pIterator->pCurrent++];
	return pIterator->pCurrentElement;
}
static void* 
get_value_c_array( void* pObject) {
	void* elem;
	get_raw_clib_object ( pObject, &elem );
	return elem;
}

static void
replace_value_c_array(struct clib_iterator *pIterator, void* elem, size_t elem_size) {
	struct clib_array*  pArray = (struct clib_array*)pIterator->pContainer;
	
	if ( pArray->destruct_fn ) {
		void* old_element;
		get_raw_clib_object ( pIterator->pCurrentElement, &old_element );
		pArray->destruct_fn(old_element);
    }
	replace_raw_clib_object( pIterator->pCurrentElement, elem, elem_size);
}

struct clib_iterator* 
new_iterator_c_array(struct clib_array* pArray) {
	struct clib_iterator *itr = malloc ( sizeof *itr );
	if (!itr)
		return NULL;
	itr->get_next   = get_next_c_array;
	itr->get_value  = get_value_c_array;
	itr->replace_value = replace_value_c_array;
	itr->pContainer = pArray;
	itr->pCurrent   = 0;
	return itr;
}
void
delete_iterator_c_array ( struct clib_iterator* pItr) {
	free ( pItr );
}
