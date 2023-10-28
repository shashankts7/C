#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct {
    char *key;
    char *value;
} hash_pair;

typedef struct {
    int size;
    int count;
    hash_pair **pairs;
} hash_table;

unsigned long hash(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

hash_pair *create_pair(char *key, char *value) {
    hash_pair *pair = malloc(sizeof(hash_pair));
    pair->key = strdup(key);
    pair->value = strdup(value);
    return pair;
}

hash_table *create_table(int size) {
    hash_table *table = malloc(sizeof(hash_table));
    table->size = size;
    table->count = 0;
    table->pairs = calloc((size_t)table->size, sizeof(hash_pair *));
    return table;
}

void free_pair(hash_pair *pair) {
    free(pair->key);
    free(pair->value);
    free(pair);
}

void free_table(hash_table *table) {
    for (int i = 0; i < table->size; i++) {
        hash_pair *pair = table->pairs[i];
        if (pair != NULL)
            free_pair(pair);
    }
    free(table->pairs);
    free(table);
}

void insert(hash_table *table, char *key, char *value) {
    unsigned long index = hash(key) % table->size;

    while (table->pairs[index] != NULL && strcmp(table->pairs[index]->key, key) != 0)
        index++;

    if (table->pairs[index] != NULL)
        free_pair(table->pairs[index]);

    table->pairs[index] = create_pair(key, value);
}

char *search(hash_table *table, char *key) {
    unsigned long index = hash(key) % table->size;

    while (table->pairs[index] != NULL && strcmp(table->pairs[index]->key, key) != 0)
        index++;

    if (table->pairs[index] == NULL)
        return NULL;
    
    return table->pairs[index]->value;
}

void delete(hash_table *table, char *key) {
    unsigned long index = hash(key) % table->size;

    while (table->pairs[index] != NULL && strcmp(table->pairs[index]->key, key) != 0)
        index++;

    if (table->pairs[index] == NULL)
        return;

    free_pair(table->pairs[index]);
    
    table->pairs[index] = NULL;
}

int main() {
    
}
