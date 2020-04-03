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
    key_value *new = new_node(key, value);
    uint16_t index = hash(key, table->size);

    key_value *cur_node = table->node[index];
    if (cur_node != NULL) {
        // have data in this index
        while (cur_node->next != NULL) {
            cur_node = cur_node->next;
        }
        cur_node->next = new;
        printf("second:    key: %s, value: %s, index: %d\n", new->key, new->value, index);
    } else {
        printf("first:    key: %s, value: %s, index: %d\n", new->key, new->value, index);
        table->node[index] = new;
    }

    table->count++;
}

char *search(hash_table *table, const char *key)
{
    uint16_t index = hash(key, table->size);
    key_value *find_node = table->node[index];
    uint16_t i = 1;
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

void traverse(hash_table *table)
{
    uint16_t i;
    for (i = 0; i < table->size; ++i) {
        key_value *tmp = table->node[i];
        if (table->node[i] != NULL) {
            printf("key: %s, value: %s, index: %d\n", tmp->key, tmp->value, i);
            while (tmp->next != NULL) {
                tmp = tmp->next;
                printf("            >>> key: %s, value: %s <<<\n", tmp->key, tmp->value);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    hash_table *table = init_table();

    uint8_t name[10];
    uint8_t num[10];
    for (uint16_t i = 1; i <= 100; i++) {
        sprintf(num, "%d", i);
        strcpy(name, "test");
        strcat(name, num);
        insert(table, name, name);
    }

    printf("\n\n==================================\n\n");
    traverse(table);
    printf("\n\n==================================\n\n");

    printf("search: %s\n", search(table, "test100"));
    printf("search: %s\n", search(table, "test50"));

    destroy_table(table);

    return 0;
}
