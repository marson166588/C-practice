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

void insert(char *data)
{
    struct slist *new_block;
    new_block = calloc(1, sizeof(struct slist *));
    strcpy(new_block->item, data);
    new_block->next = head;
    printf(">>> insert, item: %s, next: %p <<<\n", new_block->item, new_block->next);

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
        printf("point: %p, item: %s, next: %p\n", tmp, tmp->item, tmp->next);
        tmp = tmp->next;
    }
}

void search(char *data)
{
    if (head->next == NULL) {
        printf("No block\n");
        return;
    }

    int f;
    struct slist *tmp = head;
    while (tmp->next) {
        printf("data %s, item: %s\n", data, tmp->item);
        f = strcmp(tmp->item, data);
        if (f == 0) {
            printf("find\n");
            return;
        }
        tmp = tmp->next;
    }
    printf("not find\n");
}

void delete(char *data)
{
    if (head->next == NULL) {
        printf("No block\n");
        return;
    }

    printf(">>> DELETE BEFORE: <<<\n");
    list_all();

    struct slist *tmp = head;
    if (strcmp(tmp->item, data) == 0) {
        head = tmp->next;
        free(tmp);
        goto printafter;
    }

    struct slist *del_node;
    while (tmp->next) {
        if (strcmp(tmp->next->item, data) == 0) {
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

    char *buf;
    char data[10];
    int n;

    buf = calloc(1, sizeof(buf));
    while (1) {
        if (scanf("%c", buf) == 1) {
            if (*buf == 'a') {
                list_all();
            } else {
                n = scanf("%s", data);
                if (n >= 1 && n < 10) {
                    if (*buf == 'i') {
                        insert(dat);
                    } else if (*buf == 's') {
                        search(dat);
                    } else if (*buf == 'd') {
                        delete(dat);
                    }
                }
            }
        }
    }

    return 0;
}
