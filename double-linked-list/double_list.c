#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "double_list.h"

void init_block()
{
    /**
     * next   ---    prev
     *
     * tail   ---    head
     */
    tail = calloc(1, sizeof(struct dlist *));
    head = calloc(1, sizeof(struct dlist *));
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;

    printf(">>> init head: %p, tail: %p <<<\n", head, tail);
    printf(">>> head prev: %p, next: %p <<<\n", head->prev, head->next);
    printf(">>> tail prev: %p, next: %p <<<\n", tail->prev, tail->next);
}

void insert(int data)
{
    struct dlist *new_block;
    new_block = calloc(1, sizeof(struct dlist *));
    new_block->item = data;
    new_block->prev = head;
    new_block->next = head->next;
    printf(">>> insert, item: %d, next: %p <<<\n", new_block->item, new_block->next);

    head->next->prev = new_block;
    head->next       = new_block;
}

void list_all()
{
    if (head->next == tail) {
        printf("No block\n");
        return;
    }

    struct dlist *tmp = head;
    while (tmp->next) {
        if (tmp->item) {
            printf("point: %p, item: %d, next: %p\n", tmp, tmp->item, tmp->next);
        }
        tmp = tmp->next;
    }
}

void search(int data)
{
    if (head->next == tail) {
        printf("No block\n");
        return;
    }

    struct dlist *tmp = head->next;
    while (tmp->next) {
        printf("data %d, item: %d\n", data, tmp->item);
        if (tmp->item == data) {
            printf("find\n");
            return;
        }
        tmp = tmp->next;
    }
    printf("not find\n");
}

void delete(int data)
{
    if (head->next == tail) {
        printf("No block\n");
        return;
    }

    printf(">>> DELETE BEFORE: <<<\n");
    list_all();

    struct dlist *tmp = head->next;
    while (tmp->next) {
        if (tmp->item == data) {
            struct dlist *del_node;
            del_node = tmp;
            tmp->next->prev = del_node->prev;
            tmp->prev->next = del_node->next;
            free(del_node);
            goto printafter;
        }
        tmp = tmp->next;
    }

printafter:
    printf(">>> DELETE AFTER: <<<\n");
    list_all();
}

int main(int argc, char *argv[])
{
    // init
    init_block();

    char buf;
    int dat;

    while (1) {
        scanf("%c", &buf);
        if (buf == 'a') {
            list_all();
        } else {
            scanf("%d", &dat);
            if (buf == 'i') {
                insert(dat);
            } else if (buf == 's') {
                search(dat);
            } else if (buf == 'd') {
                delete(dat);
            }
        }
    }

    return 0;
}
