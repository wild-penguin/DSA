#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* prev;
    struct Node* next;
}Node;

Node* createNode(int key){
    /* Function allocates memory in heap and creates a node then returns a pointer to it. */
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->key = key;
    return node;
}


Node* listTail(Node* head){
    /* Function takes the head of a linked list and returns it's tail. */
    if (!head)
        return NULL;
    
    Node* current = head;

    while (current->next){
        current = current->next;
    }

    return current;
}


Node* arrayToList(int n, int array[]){
    /* Function takes an array and its size as arguments and returns a linked list with it's contents. */

    if (n <= 0)
        return NULL;

    Node* head = createNode(array[0]);
    Node* prev = NULL;
    Node* current = head;

    for (int i = 1; i < n; i++){
        current->next = createNode(array[i]);
        current->prev = prev;
        prev = current;
        current = current->next;
        
    }
    current->prev = prev;


    return head;
}


void printListRecursive(Node* head){
    if (!head){
        printf("NULL \n");
        return;
    }
    printf("%d <-> ", head->key);
    printListRecursive(head->next);
}


void printListRecursiveReverse(Node* tail){
    if (!tail){
        printf("NULL \n");
        return;
    }
    printf("%d <-> ", tail->key);
    printListRecursiveReverse(tail->prev);
}


void printListReverse(Node* head){
    /* Function traverses through the list (without printing anything to stdout), then it starts
       traversing in reverse and prints the node keys. */
    if (!head)
        return;
    
    Node* current = head;

    // First traversal forward
    while(current->next){
        current = current->next;
    }

    while(current){
        printf("%d <-> ", current->key);
        current = current->prev;
    }

    printf("NULL\n");
    
}


int listSumRecursive(Node* head){
    if (!head)
        return 0;
    return head->key + listSumRecursive(head->next);
}


Node* reverseList(Node* head){
    /* Function takes the head of a linked list, reverses the linked list, then returns the new head. */
    if (!head)
        return NULL;
    Node* new_head = listTail(head);
    Node* current = listTail(head);
    
    while(current){
        Node* tmp_next = current->next;
        current->next = current->prev;
        current->prev = tmp_next;
        current = current->next;
    }
    return new_head;
}


int main(){
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Node* head = arrayToList(sizeof(arr) / sizeof(arr[0]), arr);
    printListRecursive(head);
    head = reverseList(head);
    printListRecursive(head);
    return 0;
}