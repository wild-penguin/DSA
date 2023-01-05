#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int key;
    struct Node* next;
}Node;


Node* createNode(int key){
    /* Function allocates memory in heap and creates a node then returns a pointer to it. */
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->key = key;
    return node;
}


Node* arrayToList(int n, int array[]){
    /* Function takes an array and its size as arguments and returns a linked list with it's contents. */

    if (n <= 0)
        return NULL;

    Node* head = createNode(array[0]);
    Node* current = head;

    for (int i = 1; i < n; i++){
        current->next = createNode(array[i]);
        current = current->next;
    }

    return head;
}


int* listToArray(Node* head){
    /* Function takes the head of a list and returns an array with the list's contents. */
    if (!head)
        return NULL;
    
    Node* current = head;

    int size = 0;
    int* array = (int*)malloc(size);
    int i = 0;

    while (current){
        array = realloc(array, sizeof(int) * ++size);
        array[i++] = current->key;
        current = current->next;
    }

    return array;
}


void printList(Node* head){
    /* Function takes the head of a linked list and iterates through it. */
    Node* current = head;

    while (current){
        printf("%d -> ", current->key);
        current = current->next;
    }
    
    printf("NULL\n");
}


void printListRecursive(Node* head){
    if (!head){
        printf("NULL \n");
        return;
    }
    printf("%d -> ", head->key);
    printListRecursive(head->next);
}


int listSum(Node* head){
    /* Function takes the head of a linked list and returns the sum of it's keys. */
    if (!head)
        return 0;

    Node* current = head;

    int sum = 0;
    while(current){
        sum += current->key;
        current = current->next;
    }

    return sum;
}


int listSumRecursive(Node* head){
    /* Does what listSum does but with cleaner code. */
    if (!head)
        return 0;
    return head->key + listSumRecursive(head->next);
}


bool findNode(Node* head, int key){
    /* Function takes the head of a linked list and a key to search in the linked 
    list, and returns true if it exists in the linked list, else returns false. */
    if (!head)
        return false;
    
    Node* current = head;

    while (current){
        if (current->key == key)
            return true;
        current = current->next;
    }
    
    return false;
}


bool findNodeRecursive(Node* head, int key){
    if (!head)
        return false;
    if (head->key == key)
        return true;
    return findNodeRecursive(head->next, key);
}


int findAtIndex(Node* head, int index){
    /* Function takes the head of a linked list and an index. If there is a node at that index, then it returns it's key, otherwise returns 0. */
    if (!head)
        return 0;
    
    Node* current = head;

    while (current){
        if (!index)
            return current->key;
        current = current->next;
        --index;
    }

    return 0;
}


int findAtIndexRecursive(Node* head, int index){
    if (!head)
        return 0;
    if (!index){
        return head->key;
    }
    return findAtIndex(head->next, --index);
}


Node* reverseList(Node* head){
    if (!head)
        return NULL;
    
    Node* previous = NULL;
    Node* current = head;
    Node* next = head->next;

    while (current){
        current->next = previous;
        previous = current;
        current = next;
        next = next ? next->next : NULL;
    }
    return previous;
}


Node* zipperList(Node* head1, Node* head2){
    /* Function takes the heads of 2 linked lists, then creates a new list with 
    the nodes of the 2 lists zipped together (in zig zag). */
    if (!head1 || !head2)
        // if one of the lists isn't valid, return the other one, else return NULL
        return head1 ? head1 : head2 ? head2 : NULL;

    Node* current1 = head1;
    Node* current2 = head2;

    /*create the head of the zipped list (to return). This should always work because
    the function checks for valid linked lists before executing (i.e. it the lists have at least one node.) */
    Node* zipperHead = createNode(current1->key);
    Node* zipperCurrent = zipperHead;
    current1 = current1->next;

    while (current1 || current2){
        /* while loop starts with the 2nd list because a node from the first list was added previously. */
        if (current2){
            zipperCurrent->next = createNode(current2->key);
            zipperCurrent = zipperCurrent->next;
            current2 = current2->next;
        }
        if (current1){
            zipperCurrent->next = createNode(current1->key);
            zipperCurrent = zipperCurrent->next;
            current1 = current1->next;
        }
    }
    
    return zipperHead;

}


int main(){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Node* head = arrayToList(sizeof(arr) / sizeof(arr[0]), arr);
    printListRecursive(head);
    // int* arr2 = listToArray(head);
    // for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++){
    //     printf("arr2[%d] = %d\n", i, arr2[i]);
    // }
    // printf("List sum: %d\n", listSumRecursive(head));
    // printf("find: %d\n", findNodeRecursive(head, 5));
    // printf("key at index %d = %d\n", 4, findAtIndexRecursive(head, 4));
    head = reverseList(head);
    printListRecursive(head);
    int arr2[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200};
    Node* head2 = arrayToList(sizeof(arr2) / sizeof(arr2[0]), arr2);
    printListRecursive(head2);
    Node* zipped = zipperList(head, head2);
    printListRecursive(zipped);

    return 0;
}