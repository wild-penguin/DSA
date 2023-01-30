#ifndef _HASH_TABLE_FUNCTIONS_
    #define _HASH_TABLE_FUNCTIONS_

    #include <stdint.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include "hash_table_structs.h"

    unsigned long long hash(const char* key);
    struct entity_OA* initEntity_OA(const char* key, const int data);
    struct entity_SC* initEntity_SC(const char* key, const int data);
    void destroyEntity_OA(struct entity_OA* entity);
    void destroyEntity_SC(struct entity_SC* entity);
    struct hash_table_OA* initHashTable_OA(unsigned int size, const char* name);
    struct hash_table_SC* initHashTable_SC(unsigned int size, const char* name);
    void insertEntity_HashTable_OA(struct entity_OA* entity, struct hash_table_OA* table);
    void insertEntity_HashTable_SC(struct entity_SC* entity, struct hash_table_SC* table);
    void deleteEntity_HashTable_OA(struct hash_table_OA* table, const char* key);
    void deleteEntity_HashTable_SC(struct hash_table_SC* table, const char* key);
    void destroyHashTable_OA(struct hash_table_OA* table);
    void destroyHashTable_SC(struct hash_table_SC* table);
    bool lookupExists_OA(char* key, struct hash_table_OA* table);
    bool lookupExists_SC(char *key, struct hash_table_SC *table);
    void printHashTable_OA(const struct hash_table_OA* table);
    void printHashTable_SC(const struct hash_table_SC* table);
#endif
