#include "c_lib.h"
#include <stdlib.h>

void 
clib_for_each(struct clib_iterator *pIterator, void (*fn)(void*)) {
	struct clib_object *pElement;

	pElement  = pIterator->get_next(pIterator);
	while ( pElement ) {
		void *value = pIterator->get_value(pElement);
		(fn)(value);
		free ( value );
		pElement = pIterator->get_next(pIterator);
	}
}

