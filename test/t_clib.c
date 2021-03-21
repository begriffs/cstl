#include <stdio.h>
void test_c_array(void);
void test_c_deque(void);
void test_c_tree(void);
void test_c_rb(void);
void test_c_set(void);
void test_c_map(void);
void test_c_slist(void);
void test_c_map(void);
void test_c_algorithms(void);

int main( int argc, char**argv ) {	
    printf ( "Performing test for dynamic array\n");
    test_c_array();
    printf ( "Performing test for deque\n");
    test_c_deque();
    printf ( "Performing test for sets\n");
    test_c_set();
    printf ( "Performing test for map\n");
    test_c_map();
    printf ( "Performing test for slist\n");
    test_c_slist();
    printf ( "Performing algorithms tests\n");
    test_c_algorithms();

    return 0;
}
