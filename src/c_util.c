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

#include "c_lib.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void 
clib_copy( void* destination, void* source, size_t size ) {
    memcpy ( (char*)destination, source, size);
}
void
clib_get ( void* destination, void* source, size_t size) {
    memcpy ( destination, (char*)source, size);
}

struct clib_object*
new_clib_object(void* inObject, size_t obj_size) {
    struct clib_object* tmp = malloc(sizeof *tmp);
    if ( ! tmp )
        return NULL;
    tmp->size        = obj_size;
    tmp->raw_data    = malloc(obj_size);
    if ( !tmp->raw_data ) {
        free ( tmp );
        return NULL;
    }
    memcpy ( tmp->raw_data, inObject, obj_size);
    return tmp;
}

clib_error
get_raw_clib_object ( struct clib_object *inObject, void**elem) {
    *elem = malloc(inObject->size);
    if ( ! *elem )
        return CLIB_ELEMENT_RETURN_ERROR;
    memcpy ( *elem, inObject->raw_data, inObject->size );

    return CLIB_ERROR_SUCCESS;
}
void 
replace_raw_clib_object(struct clib_object* current_object,void* elem, size_t elem_size) {
	free (current_object->raw_data);
	current_object->raw_data = malloc(elem_size);
	if (current_object->raw_data)
		memcpy ( current_object->raw_data, elem, elem_size);
}


void 
delete_clib_object ( struct clib_object* inObject ) {
    if (inObject) {
        free (inObject->raw_data);
        free (inObject);
    }
}

char*
clib_strdup( const char *s ) {
    char *ret = malloc(strlen(s) + 1);
    if (ret)
        strcpy(ret, s);
    else
        errno = ENOMEM;
    return ret;
}
