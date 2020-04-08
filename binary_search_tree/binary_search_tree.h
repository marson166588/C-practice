#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct bst_node *link;
struct bst_node {
    uint16_t item;
    link left;
    link right;
};


link make_node(uint16_t item);
void free_node(link node);
link insert(link t, uint16_t item);
link search(link t, uint16_t item);
link delete(link t, uint16_t item);
void print_item(link node);
void pre_order_traverse(link t);
void in_order_traverse(link t);
void post_order_traverse(link t);

#endif
