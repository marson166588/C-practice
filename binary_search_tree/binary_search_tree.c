#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


#include "binary_search_tree.h"

link make_node(uint16_t item)
{
    link node   = malloc(sizeof(link));
    node->item  = item;
    node->left  = NULL;
    node->right = NULL;
    return node;
}

void free_node(link node)
{
    free(node);
}

link insert(link t, uint16_t item)
{
    if (t == NULL) {
        return make_node(item);
    }
    if (t->item > item) {
        t->left  = insert(t->left, item);
    } else if (t->item < item) {
        t->right = insert(t->right, item);
    }

    return t;
}

link search(link t, uint16_t item)
{
    if (t == NULL) {
        return NULL;
    }
    if (t->item > item) {
        return search(t->left, item);
    } else if (t->item < item) {
        return search(t->right, item);
    }
    return t;
}

link delete(link t, uint16_t item)
{
    if (t == NULL) {
        return NULL;
    }
    link tmp;
    if (t->item > item) {
        t->left = delete(t->left, item);
    } else if (t->item < item) {
        t->right = delete(t->right, item);
    } else {
        // t->item == item
        if (t->left == NULL && t->right == NULL) {
            // t is leaf
            free_node(t);
            t = NULL;
        } else if (t->left) {
            // if t has left subtree, replace t with the rightmost node in left subtree
            tmp = t->left;
            while (tmp->right) {
                tmp = tmp->right;
            }
            t->item = tmp->item;
            t->left = delete(t->left, t->item);
        } else if (t->right) {
            // if t has right subtree, replace t with the leftmost node in right subtree
            tmp = t->right;
            while (tmp->left) {
                tmp = tmp->left;
            }
            t->item = tmp->item;
            t->right = delete(t->right, t->item);
        }
    }
    return t;
}

void print_item(link node)
{
    printf("%d", node->item);
}

void pre_order_traverse(link t)
{
    if (t == NULL) {
        printf("()");
        return;
    }
    printf("(");
    print_item(t);
    pre_order_traverse(t->left);
    pre_order_traverse(t->right);
    printf(")");
}

void in_order_traverse(link t)
{
    if (t == NULL) {
        printf("()");
        return;
    }
    printf("(");
    in_order_traverse(t->left);
    print_item(t);
    in_order_traverse(t->right);
    printf(")");
}

void post_order_traverse(link t)
{
    if (t == NULL) {
        printf("()");
        return;
    }
    printf("(");
    post_order_traverse(t->left);
    post_order_traverse(t->right);
    print_item(t);
    printf(")");
}

int main(int argc, char *argv[])
{
    // insert
    uint16_t i, item;
    link root = NULL;
    printf("init data:\n\t");
    srand(time(NULL));
    for (i = 0; i < 6; i++) {
        item = rand() % 100;
        printf("%d ", item);
        root = insert(root, item);
    }
    printf("\n");


    // traverse
    printf("pre order traverse:\n");
    printf("\t\\tree");
    pre_order_traverse(root);
    printf("\nin order traverse:\n");
    printf("\t\\tree");
    in_order_traverse(root);
    printf("\npost order traverse:\n");
    printf("\t\\tree");
    post_order_traverse(root);

    // search delete
    printf("\n\n>>> test delete:<<<\n");
    uint16_t key;
    while (root) {
        key = rand() % 100;
        if (search(root, key)) {
            printf("delete %d in tree\n", key);
            root = delete(root, key);
            // traverse
            printf("\tpre order traverse:\n");
            printf("\t\t\\tree");
            pre_order_traverse(root);
            printf("\n\tin order traverse:\n");
            printf("\t\t\\tree");
            in_order_traverse(root);
            printf("\n\tpost order traverse:\n");
            printf("\t\t\\tree");
            post_order_traverse(root);
            printf("\n\n");
        }
    }

    return 0;
}
