#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_TABLE_SIZE  50

typedef struct KeyValue {
    char *key;
    char *value;
    struct KeyValue *next;
} key_value;

typedef struct HashTable {
    int size;
    int count;
    key_value **node;
} hash_table;

key_value *new_node(const char *k, const char *v);
hash_table *init_table();
void destroy_table(hash_table *table);
int hash(const char *key, const int m);
void insert(hash_table *table, const char *key, const char *value);
char *search(hash_table *table, const char *key);
void traverse(hash_table *table);
void delete(hash_table *table, const char *key);

#endif
