#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "hash_table_functions.h"


int main(){
    struct hash_table_SC* table = initHashTable_SC(1, "table one");

    char* names[] = {"Lola", "Lola", "Keka"};
    int datas[] = {1, 1, 3};

    insertEntity_HashTable_SC(initEntity_SC(names[0], datas[0]), table);
    insertEntity_HashTable_SC(initEntity_SC(names[1], datas[1]), table);
    insertEntity_HashTable_SC(initEntity_SC(names[1], datas[1]), table);
    insertEntity_HashTable_SC(initEntity_SC(names[2], datas[2]), table);
    deleteEntity_HashTable_SC(table, "Lola");
    deleteEntity_HashTable_SC(table, "Keka");
    deleteEntity_HashTable_SC(table, "My ass");
    deleteEntity_HashTable_SC(table, "Lola");
    deleteEntity_HashTable_SC(table, "Lola");
    deleteEntity_HashTable_SC(table, "Lola");

    printHashTable_SC(table);
    destroyHashTable_SC(table);
    return 0;
}