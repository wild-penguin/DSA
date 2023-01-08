#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    void* data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct Queue{
    unsigned int size;
    Node** queue;
}Queue;


Node* nodeInit(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;    
}


Queue* queueInit(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = 0;
    queue->queue = (Node**)malloc(sizeof(0));
    return queue;
}


int queuePush(Queue* queue, Node* node){
    if (!queue || !node)
        return EXIT_FAILURE;
    
    queue->size += 1;
    queue->queue = (Node**)realloc(queue->queue, sizeof(Node*) * queue->size);
    queue->queue[queue->size - 1] = node;
    
    return EXIT_SUCCESS;
}


Node* queuePop(Queue* queue){
    if(!queue || !queue->size)
        return NULL;
    
    Node* ret = queue->queue[0];
    queue->size -= 1;

    if (queue->size){
        memcpy(queue->queue, queue->queue + 1, sizeof(Node*) * queue->size);
    }
    
    return ret;
}


int treePush(Node* root, Node* node){
    if (!root || !node)
        return EXIT_FAILURE;
    
    Node* current = root;

    while (current){
        if (node->key > current->key){ // if node to be inserted has a bigger key value than current node
            if (current->right){    // if current node has a right child
                current = current->right; // current = current right child
                continue;
            }
            else { // if first condition isn't true, then current has no right child
                current->right = node; // current's right child is now the node
                return EXIT_SUCCESS;
            }
        }
        else if (node->key < current->key){ // if node to be inserted has lesser key value than current node
            if (current->left){ // if current node has a left child
                current = current->left; // current = current left child
                continue;
            }
            else { // if first condition isn't true, then current has no left child
                current->left = node; // current's left child is now the node
                return EXIT_SUCCESS;
            }
        }
        else{ // if first 2 conditions aren't true, then the node is a duplicate
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}


Node* arrayToTree(int n, int arr[]){
    if (!n || !arr)
        return NULL;

    Node* root = nodeInit(arr[0]);

    for (int i = 1; i < n; i++)
        treePush(root, nodeInit(arr[i]));
    
    return root;
    
}


int* treeToArrayBFS(Node* root){
    if (!root)
        return NULL;

    Queue* queue = queueInit();
    queuePush(queue, root);
    int* node_keys = (int*)malloc(0);
    unsigned int node_keys_len = 0;

    while (queue->size){
        Node* current = queuePop(queue);

        if (current->left)
            queuePush(queue, current->left);
        if (current->right)
            queuePush(queue, current->right);

        node_keys = realloc(node_keys, ++node_keys_len * sizeof(int));
        node_keys[node_keys_len - 1] = current->key;
    }

    free(queue);
    return node_keys;

}


unsigned int treeSize(Node* root){
    if (!root)
        return 0;
    
    unsigned int tree_size = 0;
    Queue* queue = queueInit();
    queuePush(queue, root);

    while (queue->size){
        Node* current = queuePop(queue);

        if (current->left)
            queuePush(queue, current->left);
        if (current->right)
            queuePush(queue, current->right);
        ++tree_size;
    }
    free(queue);
    return tree_size;
}


int main(){
    int arr[] = {7, 2, 9, 1, 3, 8, 1000};
    Node* root = arrayToTree(7, arr);

    int* keys = treeToArrayBFS(root);

    for (int i = 0; i < treeSize(root); i++){
        printf("keys[%d] = %d\n", i, keys[i]);
    }
    return 0;
}