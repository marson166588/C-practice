#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

typedef struct dlist {
    struct dlist *prev;
    int item;
    struct dlist *next;
} list;

struct dlist *head = NULL;
struct dlist *tail = NULL;

void init_block();
void insert();
void list_all();
void search();
void delete();

#endif
