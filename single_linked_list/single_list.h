#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

typedef struct slist {
    int item;
    struct slist *next;
} list;
struct slist *head = NULL;

void init_block();
void insert();
void list_all();
void search();
void delete();

#endif
