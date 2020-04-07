#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "hash_table.h"

key_value *new_node(const char *k, const char *v)
{
    key_value *node = malloc(sizeof(key_value));
    node->key       = strdup(k);
    node->value     = strdup(v);

    return node;
}

hash_table *init_table()
{
    hash_table *table = malloc(sizeof(hash_table));
    table->size       = HASH_TABLE_SIZE;
    table->count      = 0;
    table->node       = (key_value **)calloc(table->size, sizeof(key_value *));

    return table;
}

void destroy_table(hash_table *table)
{
    uint16_t i;
    for (i = 0; i < table->size; i++) {
        key_value *node = table->node[i];
        if (node != NULL) {
            free(node->key);
            free(node->value);
            free(node);
        }
    }
    free(table->node);
    free(table);
}

int hash(const char *key, const int m) {
    uint16_t hash = 0;

    for (uint16_t i = 0; i < key[i] != '\0'; ++i) {
        hash = hash * 31 + key[i];
    }

    return abs(hash % m);
}

void insert(hash_table *table, const char *key, const char *value)
{
    uint16_t index = hash(key, table->size);
    key_value *cur_node = table->node[index];
    if (cur_node != NULL) {
        if (strcmp(cur_node->key, key) == 0) {
            // replace value
            cur_node->value = strdup(value);
            return;
        }
        // have data in this index
        while (cur_node->next != NULL) {
            cur_node = cur_node->next;
            if (strcmp(cur_node->key, key) == 0) {
                // replace value
                cur_node->value = strdup(value);
                return;
            }
        }

        cur_node->next = new_node(key, value);
    } else {
        table->node[index] = new_node(key, value);
    }

    table->count++;
}

char *search(hash_table *table, const char *key)
{
    uint16_t index = hash(key, table->size);
    key_value *find_node = table->node[index];
    if (find_node != NULL) {
        if (strcmp(find_node->key, key) == 0) {
            return find_node->value;
        }

        while (find_node->next != NULL) {
            find_node = find_node->next;
            if (strcmp(find_node->key, key) == 0) {
                return find_node->value;
            }
        }
    }

    return NULL;
}

void delete(hash_table *table, const char *key)
{
    uint16_t index = hash(key, table->size);
    key_value *find_node = table->node[index];

    if (find_node != NULL) {
        if (strcmp(find_node->key, key) == 0) {
            // if has linked list, node index = first linked list
            if (find_node->next != NULL) {
                table->node[index] = find_node->next;
            }
            free(find_node);
            return;
        }

        // if has linked list, move linked list to node index
        while (find_node->next != NULL) {
            if (strcmp(find_node->next->key, key) == 0) {
                key_value *tmp = find_node->next;
                if (find_node->next->next != NULL) {
                    find_node->next = find_node->next->next;
                } else {
                    find_node->next = NULL;
                }
                free(tmp);
                return;
            }
            find_node = find_node->next;
        }
    }
}

void traverse(hash_table *table)
{
    uint16_t i;
    for (i = 0; i < table->size; ++i) {
        key_value *tmp = table->node[i];
        if (table->node[i] != NULL) {
            printf("key: %s, value: %s, index: %d\n", tmp->key, tmp->value, i);
            while (tmp->next != NULL) {
                tmp = tmp->next;
                printf("    key: %s, value: %s\n", tmp->key, tmp->value);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    hash_table *table = init_table();

    printf(">>>test insert:<<<\n");
    uint8_t name[10];
    uint8_t num[10];
    for (uint16_t i = 1; i <= 100; i++) {
        sprintf(num, "%d", i);
        strcpy(name, "test");
        strcat(name, num);
        insert(table, name, name);
    }
    // exist key, replace value
    insert(table, "test29", "TEST29");

    printf(">>>test traverse:<<<\n");
    traverse(table);
    printf("==================================\n\n");

    printf(">>>test search:<<<\n");
    printf("search: %s\n", search(table, "test100"));
    printf("search: %s\n", search(table, "test50"));
    printf("==================================\n\n");

    printf(">>>test delete:<<<\n");
    delete(table, "test92");
    delete(table, "test6");
    delete(table, "test89");
    traverse(table);

    destroy_table(table);

    return 0;
}
