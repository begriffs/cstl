#include "c_lib.h"

struct clib_slist* 
new_c_slist(clib_destroy fn_d, clib_compare fn_c){
    struct clib_slist* pSlist = malloc(sizeof *pSlist);
    if (!pSlist)
        return NULL;
    pSlist->head           = NULL;
    pSlist->destruct_fn    = fn_d;
    pSlist->compare_key_fn = fn_c;
    pSlist->size           = 0;
    return pSlist;
}
void           
delete_c_slist( struct clib_slist* pSlist){
    while(pSlist->size != 0) {
        remove_c_slist ( pSlist, 0 );
    }
    free ( pSlist );
}

clib_error           
push_back_c_slist( struct clib_slist* pSlist, void* elem, size_t elem_size){

    struct clib_slist_node* current  = NULL;
    struct clib_slist_node* new_node = NULL;

    new_node = malloc(sizeof *new_node);
    if (!new_node)
        return CLIB_SLIST_INSERT_FAILED;

    new_node->elem = new_clib_object ( elem, elem_size );
    if ( ! new_node->elem )
        return CLIB_SLIST_INSERT_FAILED;
    new_node->next = NULL;

    if ( !pSlist->head ) {
        pSlist->head = new_node;
        pSlist->size++;
        return CLIB_ERROR_SUCCESS;
    }
    current = pSlist->head;
    while ( current->next )
        current  = current->next;    
    current->next = new_node;
    pSlist->size++;

    return CLIB_ERROR_SUCCESS;
}
static void 
_remove_c_list ( struct clib_slist* pSlist, struct clib_slist_node* pSlistNode ) {
    void* elem;
    get_raw_clib_object(pSlistNode->elem, &elem);
    if ( pSlist->destruct_fn) {             
        (pSlist->destruct_fn)(elem);
        delete_clib_object ( pSlistNode->elem );
    }else {
        free ( elem );
        delete_clib_object ( pSlistNode->elem );
    }        
    free ( pSlistNode);
}
void           
remove_c_slist( struct clib_slist* pSlist, size_t pos ) {
    size_t i = 0;

    struct clib_slist_node* current = pSlist->head;
    struct clib_slist_node* temp    = NULL;

    if ( pos > pSlist->size ) return;

    if ( pos == 0 ) {                
        pSlist->head = current->next;    
        _remove_c_list(pSlist, current);
        pSlist->size--;
        return;
    }
    for ( i = 1; i < pos - 1; i++)
        current = current->next;

    temp          = current->next;
    current->next = current->next->next;
    _remove_c_list ( pSlist, temp );

    pSlist->size--;
}
clib_error           
insert_c_slist(struct clib_slist* pSlist, size_t pos, void* elem, size_t elem_size) {
    size_t i = 0;
    struct clib_slist_node* current  = pSlist->head;
    struct clib_slist_node* new_node = NULL;
   
    if ( pos == 1 ) {
        new_node       = malloc(sizeof *new_node);
        if (!new_node)
            return CLIB_SLIST_INSERT_FAILED;
        new_node->elem = new_clib_object ( elem, elem_size );
        if ( ! new_node->elem ) {
            free ( new_node );
            return CLIB_SLIST_INSERT_FAILED;
        }
        new_node->next = pSlist->head;
        pSlist->head       = new_node;
        pSlist->size++;
        return CLIB_ERROR_SUCCESS;
    }

    if ( pos >= pSlist->size + 1 ) {
        return push_back_c_slist ( pSlist, elem, elem_size );
    }

    for ( i = 1; i < pos - 1; i++) {
        current = current->next;
    }
    new_node       = malloc(sizeof *new_node);
    if ( ! new_node )
        return CLIB_SLIST_INSERT_FAILED;
    new_node->elem = new_clib_object ( elem, elem_size );
    if ( ! new_node->elem ) {
        free ( new_node );
        return CLIB_SLIST_INSERT_FAILED;
    }

    new_node->next = current->next;
    current->next  = new_node;
    pSlist->size++;

    return CLIB_ERROR_SUCCESS;
}
void           
for_each_c_slist (struct clib_slist* pSlist, void (*fn)(void* )) {
    void* elem;
    struct clib_slist_node* current  = pSlist->head;
    while ( current ) {
        get_raw_clib_object(current->elem, &elem);
        (fn)(elem);
        free ( elem );
        current = current->next;
    }    
}
clib_bool
find_c_slist (struct clib_slist* pSlist, void* find_value, void**out_value) {
    struct clib_slist_node* current  = pSlist->head;  
    while ( current ) {
        get_raw_clib_object(current->elem, out_value);
        if ((pSlist->compare_key_fn)(find_value,*out_value) != 0){
            break;
        }
        free ( *out_value );
        current = current->next;
    }
    if ( current ) {
        return clib_true;
    }
    return clib_false;
}


static struct clib_object* 
get_next_c_slist( struct clib_iterator* pIterator ) {

	struct clib_slist *pSlist = (struct clib_slist*)pIterator->pContainer;
	if ( ! pIterator->pCurrentElement ) {
		pIterator->pCurrentElement = (struct clib_slist_node*)pSlist->head;
	}else {
		pIterator->pCurrentElement = ((struct clib_slist_node*)pIterator->pCurrentElement)->next;
	}
	if ( ! pIterator->pCurrentElement)
		return NULL;

	return ((struct clib_slist_node*)pIterator->pCurrentElement)->elem;
}

static void* 
get_value_c_slist( void* pObject) {
	void* elem;
	get_raw_clib_object ( pObject, &elem );
	return elem;
}

static void
replace_value_c_slist(struct clib_iterator *pIterator, void* elem, size_t elem_size) {
	struct clib_slist*  pSlist = (struct clib_slist*)pIterator->pContainer;
	struct clib_object *pObj = ((struct clib_slist_node*)pIterator->pCurrentElement)->elem;
	
	if ( pSlist->destruct_fn ) {
		void* old_element;
		
		get_raw_clib_object (pObj, &old_element );
		pSlist->destruct_fn(old_element);
    }
	replace_raw_clib_object( pObj, elem, elem_size);
}

struct clib_iterator* 
new_iterator_c_slist(struct clib_slist* pSlist) {
	struct clib_iterator *itr = malloc ( sizeof *itr );
	if (!itr)
		return NULL;
	itr->get_next      = get_next_c_slist;
	itr->get_value     = get_value_c_slist;
	itr->replace_value = replace_value_c_slist;
	itr->pContainer     = pSlist;
	itr->pCurrentElement = NULL;
	itr->pCurrent      = 0;
	return itr;
}
void
delete_iterator_c_slist ( struct clib_iterator* pItr) {
	free ( pItr );
}
