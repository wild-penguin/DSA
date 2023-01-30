#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "hash_table_functions.h"


int main(){
    struct hash_table_SC* table = initHashTable_SC(1, "table one");

    char* names[] = {"A", "B", "C"};
    int data[] = {1, 2, 3};

    insertEntity_HashTable_SC(initEntity_SC(names[0], data[0]), table);
    insertEntity_HashTable_SC(initEntity_SC(names[1], data[1]), table);
    insertEntity_HashTable_SC(initEntity_SC(names[2], data[2]), table);
    deleteEntity_HashTable_SC(table, "A");
    
    printHashTable_SC(table);
    
    deleteEntity_HashTable_SC(table, "Z");

    printHashTable_SC(table);
    
    destroyHashTable_SC(table);
    return 0;

}

// output:
/*
initHashTable: 'table one': Successfully initiated.
insertEntity: 'A': inserted in table 'table one'.
insertEntity: 'B': inserted in table 'table one'.
insertEntity: 'C': inserted in table 'table one'.
deleteEntity: 'A' : deleted from table 'table one'.
========== Printing table 'table one' ==========
'B' --- '2'
        'C' --- '3'
====================
deleteEntity: 'Z' : Failed deleton : key not found in table 'table one'.
========== Printing table 'table one' ==========
'B' --- '2'
        'C' --- '3'
====================
destroyHashTable: 'table one': destroyed succesfully.
*/




