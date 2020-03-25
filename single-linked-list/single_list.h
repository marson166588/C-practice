#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

typedef struct slist {
    char item[10];
    struct slist *next;
} list;
struct slist *head = NULL;

void init_block();
void insert();
void list_all();
void search();
void delete();
#endif
