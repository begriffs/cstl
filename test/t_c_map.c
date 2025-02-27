#include "c_lib.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

static int
compare_e ( void* left, void* right ) {
    return strcmp ( (const char *)left, (const char *) right );
}
char *char_value[] = {  "A","B","C","D","E","F","G","H","I","J","K","L","M",
                        "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
int int_value[] = { 1,2,3,4,5,6,7,8,9,10,
                      11,12,13,14,15,16,17,18,19,20,
                      21,22,23,24,25,26};

static void 
insert_all ( struct clib_map* myMap) {
    int size = sizeof(char_value)/sizeof(char_value[0]);
    int i = 0;
    for ( i = 0; i < size; i++ ) {
        char *key = clib_strdup( char_value[i]);
        int key_length = (int)strlen ( key ) + 1;
        int value = int_value[i];
		printf ( "Inserting [%s -> %d]\n", key, value );
        insert_c_map ( myMap, key, key_length, &value, sizeof(int)); 
        free ( key );
    }
}
static void 
check_exists_all( struct clib_map* myMap) {
    int size = sizeof(char_value)/sizeof(char_value[0]);
    int i = 0;
    for ( i = 0; i < size; i++ ) {
        void* value ;
        assert ( clib_true == exists_c_map ( myMap, char_value[i]));
        assert ( clib_true == find_c_map( myMap, char_value[i], &value));
		printf ( "-----> [%s == %d]\n", char_value[i], *(int*)value);
        assert ( *(int*)value == int_value[i]);
        free ( value );
    }
}

static void 
remove_some_exist(struct clib_map* myMap) {
    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "A"));
    assert ( clib_false == exists_c_map ( myMap, "A"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "X"));
    assert ( clib_false == exists_c_map ( myMap, "X"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "Z"));
    assert ( clib_false == exists_c_map ( myMap, "Z"));

    assert ( CLIB_ERROR_SUCCESS == remove_c_map ( myMap, "H"));
    assert ( clib_false == exists_c_map ( myMap, "H"));
}
static void
add_removed_check_all(struct clib_map* myMap) {

    char *key       = clib_strdup ("A");
    int  key_length = (int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length , &int_value[0], sizeof(int)); 
    free ( key );

    key        = clib_strdup ("X");
    key_length = (int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length, &int_value[23], sizeof(int)); 
    free ( key );

    key        = clib_strdup ("Z");
    key_length = (int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length, &int_value[25], sizeof(int)); 
    free ( key );

    key        = clib_strdup ("H");
    key_length = (int)strlen ( key ) + 1;
    insert_c_map ( myMap, key, key_length, &int_value[7 ], sizeof(int)); 
    free ( key );

    check_exists_all(myMap);
}
static void
print_using_iterator( struct clib_map *myMap) {
	struct clib_iterator *myItr;
	struct clib_object *pElement;
	printf ( "------------------------------------------------\n");
	myItr     = new_iterator_c_map (myMap);
	pElement  = myItr->get_next(myItr);
	while ( pElement ) {
		void* value = myItr->get_value(pElement);
		printf ( "%d\n", *(int*)value);
		free ( value );
		pElement = myItr->get_next(myItr);
	}
	delete_iterator_c_map( myItr );
}

static void 
replace_values_using_iterators(struct clib_map* myMap) {
	struct clib_iterator *myItr;
	struct clib_object *pElement;
	printf ( "------------------------------------------------\n");
	myItr     = new_iterator_c_map (myMap);
	pElement  = myItr->get_next(myItr);
	while ( pElement ) {
		void* old_value = myItr->get_value(pElement);
		int new_value = *(int*)old_value;
		new_value = new_value * 2;
		myItr->replace_value( myItr, &new_value, sizeof(new_value));
		free ( old_value );

		pElement = myItr->get_next(myItr);
	}
	delete_iterator_c_map( myItr );
}

static void
test_with_iterators() {
	struct clib_map* myMap = new_c_map ( compare_e, NULL, NULL);
	insert_all(myMap);
	print_using_iterator(myMap);
	replace_values_using_iterators(myMap);
	print_using_iterator(myMap);
	delete_c_map(myMap);
}


void 
test_c_map() {
    struct clib_map* myMap = new_c_map ( compare_e, NULL, NULL);
    insert_all(myMap);
    check_exists_all(myMap);   
    remove_some_exist(myMap);
    add_removed_check_all(myMap);
    delete_c_map(myMap);
	test_with_iterators();
}
