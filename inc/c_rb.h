#ifndef C_RB_H
#define C_RB_H

struct clib_rb_node {
    struct clib_rb_node *left;
    struct clib_rb_node *right;
    struct clib_rb_node *parent;
    int color; 
    struct clib_object* key;
    struct clib_object* value; 
};

struct clib_rb {
    struct clib_rb_node* root;
    struct clib_rb_node sentinel;
    clib_destroy destruct_k_fn;
	clib_destroy destruct_v_fn;
    clib_compare compare_fn;
};

struct clib_rb* new_c_rb(clib_compare fn_c,clib_destroy fn_ed, clib_destroy fn_vd );
clib_error  insert_c_rb(struct clib_rb* pTree, void* key, size_t key_size, void* value, size_t value_size);
struct clib_rb_node*   find_c_rb (struct clib_rb* pTree, void* key);
struct clib_rb_node* remove_c_rb (struct clib_rb* pTree, void* key);
clib_error  delete_c_rb (struct clib_rb* pTree);
clib_bool   empty_c_rb  (struct clib_rb* pTree);

struct clib_rb_node *minimum_c_rb( struct clib_rb* pTree, struct clib_rb_node* x );
struct clib_rb_node* tree_successor(struct clib_rb* pTree, struct clib_rb_node* x);

#endif
