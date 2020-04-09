#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "single_list.h"

void init_block()
{
    head = calloc(1, sizeof(struct slist *));
    printf(">>>init head: %p<<<\n", head);
}

void insert(int data)
{
    struct slist *new_block;
    new_block = calloc(1, sizeof(struct slist *));
    new_block->item = data;
    new_block->next = head;
    printf(">>> insert, item: %d, next: %p <<<\n", new_block->item, new_block->next);

    head = new_block;
}

void list_all()
{
    if (head->next == NULL) {
        printf("No block\n");
        return;
    }

    struct slist *tmp = head;
    while (tmp->next) {
        printf("point: %p, item: %d, next: %p\n", tmp, tmp->item, tmp->next);
        tmp = tmp->next;
    }
}

void search(int data)
{
    if (head->next == NULL) {
        printf("No block\n");
        return;
    }

    struct slist *tmp = head;
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
    if (head->next == NULL) {
        printf("No block\n");
        return;
    }

    printf(">>> DELETE BEFORE: <<<\n");
    list_all();

    struct slist *tmp = head;
    if (tmp->item == data) {
        head = tmp->next;
        free(tmp);
        goto printafter;
    }

    struct slist *del_node;
    while (tmp->next) {
        if (tmp->next->item == data) {
            // find
            del_node = tmp->next;
            tmp->next = tmp->next->next;
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
