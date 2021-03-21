#ifndef C_LIB_H
#define C_LIB_H

#include "c_errors.h"
#include <stdlib.h>

/* ------------------------------------------------------------------------*/
/*       C O M M O N       D E F I N I T O N S                             */
/* ------------------------------------------------------------------------*/

typedef void (*clib_destroy)(void*);
typedef int  (*clib_compare)(void*,void*);
typedef void (*clib_traversal)( void*);

typedef int  clib_bool;

#define clib_black           0
#define clib_red             1
#define clib_true            1
#define clib_false           0

/* ------------------------------------------------------------------------*/
/*                            P  A  I   R                                  */
/* ------------------------------------------------------------------------*/

struct clib_object {
    void* raw_data;
    size_t size;
};


struct clib_iterator {
	struct clib_object* (*get_next)(struct clib_iterator*);
	void (*replace_value)(struct clib_iterator*,void*,size_t);
	void* (*get_value)(void*);
	void* pContainer;
	size_t pCurrent;
	void* pCurrentElement;
};

#include "c_array.h"
#include "c_deque.h"
#include "c_rb.h"
#include "c_set.h"
#include "c_map.h"
#include "c_slist.h"
#include "c_map.h"
#include "c_algorithms.h"

/* ------------------------------------------------------------------------*/
/*            H E L P E R       F U N C T I O N S                          */
/* ------------------------------------------------------------------------*/

void  clib_copy ( void* destination, void* source, size_t size );
void  clib_get  ( void* destination, void* source, size_t size);
char* clib_strdup ( const char *s );

struct clib_object* new_clib_object (void* inObject, size_t obj_size);
clib_error get_raw_clib_object (struct clib_object *inObject, void**elem);
void  delete_clib_object  (struct clib_object* inObject );
void replace_raw_clib_object(struct clib_object* current_object,void* elem, size_t elem_size);

#endif
