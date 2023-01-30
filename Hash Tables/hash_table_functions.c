#include "hash_table_functions.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash_table_structs.h"


unsigned long long hash(const char* key){
    /* extremely basic hash function */
    if (!key)
        return 0;
    
    unsigned long long sum = 0;

    for (int i = 0; i < strlen(key); i++){
        sum += key[i] * (i + 1);
    }
    return sum;
}


struct entity_OA* initEntity_OA(const char* key, const int data){
    struct entity_OA* ret = (struct entity_OA*)malloc(sizeof(struct entity_OA));
    ret->key = (char*)malloc(strlen(key) + 1);
    strcpy(ret->key, key);
    ret->data = data;
    return ret;
}


struct entity_SC* initEntity_SC(const char* key, const int data){
    struct entity_SC* ret = (struct entity_SC*)malloc(sizeof(struct entity_SC));
    ret->key = (char*)malloc(strlen(key) + 1);
    strcpy(ret->key, key);
    ret->data = data;
    ret->next = NULL;
    return ret;
}


void destroyEntity_OA(struct entity_OA* entity){
    if (!entity)
        return;
    free(entity->key);
    free(entity);
}


void destroyEntity_SC(struct entity_SC* entity){
    if (!entity)
        return;
    free(entity->key);
    free(entity);
}


struct hash_table_OA* initHashTable_OA(unsigned int size, const char* name){
    if (size <= 0)
        return NULL;
    
    struct hash_table_OA* ret = (struct hash_table_OA*)malloc(sizeof(struct hash_table_OA));
    ret->table = (struct entity_OA**)malloc(sizeof(struct entity_OA*) * size);
    ret->name = (char*)malloc(strlen(name) + 1);
    strcpy(ret->name, name);
    
    for (int i = 0; i < size; i++){
        ret->table[i] = NULL;
    }
    ret->size = size;
    printf("initHashTable: '%s': Successfully initiated.\n", ret->name);
    return ret;
}


struct hash_table_SC* initHashTable_SC(unsigned int size, const char* name){
    if (size <= 0)
        return NULL;
    
    struct hash_table_SC* ret = (struct hash_table_SC*)malloc(sizeof(struct hash_table_SC));
    ret->table = (struct entity_SC**)malloc(sizeof(struct entity_SC*) * size);
    ret->name = (char*)malloc(strlen(name) + 1);
    strcpy(ret->name, name);
    
    for (int i = 0; i < size; i++){
        ret->table[i] = NULL;
    }

    ret->size = size;
    printf("initHashTable: '%s': Successfully initiated.\n", ret->name);
    return ret;
}


void insertEntity_HashTable_OA(struct entity_OA* entity, struct hash_table_OA* table){
    if (!entity || !table)
        return;
    
    unsigned long long index = hash(entity->key) % table->size;
    if (!table->table[index]){
        table->table[index] = entity;
        printf("insertEntity: '%s': inserted in table '%s'.\n", entity->key, table->name);
        return;
    }
    int i = 1;
    unsigned long long int collision_index = (index + i) % table->size;
    for (i = 1; i < table->size; i++){
        collision_index = (index + i) % table->size;
        if (!table->table[(index + i) % table->size]){
            table->table[(index + i) % table->size] = entity;
            printf("insertEntity: '%s': inserted in table '%s'.\n", entity->key, table->name);
            return;
        }
    }
    printf("insertEntity: '%s': failed to insert in table '%s'. Likely the table is full.\n", entity->key, table->name);
}


void insertEntity_HashTable_SC(struct entity_SC* entity, struct hash_table_SC* table){
    if (!entity || !table)
        return;
    
    unsigned long long index = hash(entity->key) % table->size;
    if (!table->table[index]){
        table->table[index] = entity;
        printf("insertEntity: '%s': inserted in table '%s'.\n", entity->key, table->name);
        return;
    }

    struct entity_SC* traversal = table->table[index];
    
    while (traversal->next)
        traversal = traversal->next;
    
    traversal->next = entity;
    printf("insertEntity: '%s': inserted in table '%s'.\n", entity->key, table->name);

}


void deleteEntity_HashTable_OA(struct hash_table_OA* table, const char* key){
    if (!table || !key)
        return;
    
    unsigned long long int index = hash(key) % table->size;

    if(!table->table[index])
        return;
    
    if (table->table[index] && !strcmp(key, table->table[index]->key)){
        destroyEntity_OA(table->table[index]);
        table->table[index] = NULL;
        printf("deleteEntity: '%s': deleted from table '%s'.\n", key, table->name);
        return;
    }
    int i = 1;
    unsigned long long collision_index = (index + i) % table->size;
    for (i = 1; i < table->size; i++){
        collision_index = (index + i) % table->size;

        if (table->table[collision_index] && !strcmp(key, table->table[collision_index]->key)){
            destroyEntity_OA(table->table[collision_index]);
            table->table[collision_index] = NULL;
            printf("deleteEntity: '%s': deleted from table '%s'.\n", key, table->name);
        return;
    }
    }

    printf("deleteEntity: '%s': Failed deleton : key not found in table '%s'.\n", key, table->name);

}


void deleteEntity_HashTable_SC(struct hash_table_SC* table, const char* key){
    if (!table || !key)
        return;
    
    unsigned long long int index = hash(key) % table->size;

    if(!table->table[index])
        return;
    
    if (table->table[index] && !strcmp(key, table->table[index]->key)){
        struct entity_SC** temp = &table->table[index]->next;

        destroyEntity_SC(table->table[index]);
        table->table[index] = *temp ? *temp : NULL;
        printf("deleteEntity: '%s' : deleted from table '%s'.\n", key, table->name);
        return;
    }

    struct entity_SC* traversal = table->table[index];
    struct entity_SC* traversal_previous = NULL;

    while(traversal){
        if (!strcmp(traversal->key, key)){
            traversal_previous->next = traversal->next;
            destroyEntity_SC(traversal);
            printf("deleteEntity: '%s' : deleted from table '%s'.\n", key, table->name);
            return;
        }
        traversal_previous = traversal;
        traversal = traversal->next;
    }
    printf("deleteEntity: '%s' : Failed deleton : key not found in table '%s'.\n", key, table->name);

}


void destroyHashTable_OA(struct hash_table_OA* table){
    if (!table)
        return;
    
    char* table_name = (char*)malloc(strlen(table->name) + 1);
    strcpy(table_name, table->name);

    for (int i = 0; i < table->size; i++){
        destroyEntity_OA(table->table[i]);
    }

    free(table->table);
    printf("destroyHashTable: '%s': destroyed succesfully.\n", table_name);
    free(table_name);
}


void destroyHashTable_SC(struct hash_table_SC* table){
    if (!table)
        return;

    char* table_name = (char*)malloc(strlen(table->name) + 1);
    strcpy(table_name, table->name);


    for (int i = 0; i < table->size; i++){
        destroyEntity_SC(table->table[i]);
    }

    free(table->table);
    printf("destroyHashTable: '%s': destroyed succesfully.\n", table_name);
    free(table_name);
}


bool lookupExists_OA(char* key, struct hash_table_OA* table){
    if(!key || !table)
        return false;
    
    unsigned long long index = hash(key) % table->size;

    if (!table->table[index])
        return false;

    if (!strcmp(table->table[index]->key, key))
        return true;

    for(int i = 0; i < table->size; i++){
        if (!table->table[(i + index) % table->size])
            return false;

        if (!strcmp(table->table[(i + index) % table->size]->key, key))
            return true;
    }
    return false;
}


bool lookupExists_SC(char *key, struct hash_table_SC *table){
    if(!key || !table)
        return false;
    
    unsigned long long index = hash(key) % table->size;

    if (!table->table[index])
        return false;

    if (!strcmp(table->table[index]->key, key))
        return true;
    
    struct entity_SC* traversal = table->table[index];

    while(traversal){
        if (!strcmp(traversal->key, key))
            return true;
        traversal = traversal->next;
    }

    return false;
    
}


void printHashTable_OA(const struct hash_table_OA* table){
    if (!table)
        return;
    
    printf("========== Printing table '%s' ==========\n", table->name);

    for (int i = 0; i < table->size; i++){
        if (!table->table[i])
            printf("NULL\n");
        else
            printf("'%s' --- '%d'\n", table->table[i]->key, table->table[i]->data);
    }
    printf("====================\n");
}


void printHashTable_SC(const struct hash_table_SC* table){
    if (!table)
        return;

    printf("========== Printing table '%s' ==========\n", table->name);

    for (int i = 0; i < table->size; i++){
        if (!table->table[i])
            printf("NULL\n");
        else{
            printf("'%s' --- '%d'\n", table->table[i]->key, table->table[i]->data);
            struct entity_SC* traversal = table->table[i]->next;
            
            while(traversal){
                printf("\t'%s' --- '%d'\n", traversal->key, traversal->data);
                traversal = traversal->next;
            }
        }
    }
    printf("====================\n");
}
