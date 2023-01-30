#ifndef _HASH_TABLE_STRUCTS_
    #define _HASH_TABLE_STRUCTS_

    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>

    typedef struct entity_OA{
        /* hash table member. open addressing */
        char* key;
        // void* data;
        int data;
    }entity;

    typedef struct entity_SC{
        /* hash table member. separate chaining */
        char* key;
        // void* data;
        int data;
        struct entity_SC* next;
    }entity_SC;

    typedef struct hash_table_OA{
        char* name;
        unsigned int size;
        struct entity_OA** table;
    }hash_table_OA;

    typedef struct hash_table_SC{
        char* name;
        unsigned int size;
        struct entity_SC** table;
    }hash_table_SC;
    

#endif