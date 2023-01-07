#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int key;
    void* data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct Stack{
    unsigned int size;
    Node** stack;
}Stack;


Node* nodeInit(int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;    
}


Stack* stackInit(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->size = 0;
    stack->stack = (Node**)malloc(0);
    return stack;
}


int stackPush(Stack* stack, Node* node){
    if (!stack || !node)
        return EXIT_FAILURE;
    
    stack->size += 1;
    stack->stack = (Node**)realloc(stack->stack, sizeof(Node*) * stack->size);
    stack->stack[stack->size - 1] = node;
    
    return EXIT_SUCCESS;
}


Node* stackPop(Stack* stack){
    if (!stack || !stack->size)
        return NULL;
    
    Node* ret = stack->stack[stack->size - 1];
    stack->size -= 1;
    stack->stack = (Node**)realloc(stack->stack, sizeof(Node*) * stack->size);

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


int* treeToArrayDFS(Node* root){
    if (!root)
        return NULL;
    
    Stack* stack = stackInit();
    stackPush(stack, root);
    int* node_keys = (int*)malloc(0);
    unsigned int node_keys_len = 0;

    while (stack->size){
        Node* current = stackPop(stack);

        if (current->right)
            stackPush(stack, current->right);
        if (current->left)
            stackPush(stack, current->left);
        
        node_keys = realloc(node_keys, ++node_keys_len * sizeof(int));
        node_keys[node_keys_len - 1] = current->key;
    }

    free(stack);
    return node_keys;
}


unsigned int treeSize(Node* root){
    if (!root)
        return 0;
    
    unsigned int tree_size = 0;
    Stack* stack = stackInit();
    stackPush(stack, root);

    while (stack->size){
        Node* current = stackPop(stack);

        if (current->right)
            stackPush(stack, current->right);
        if (current->left)
            stackPush(stack, current->left);
        
        ++tree_size;
    }

    return tree_size;
    
}


int main(){
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1};
    Node* root = arrayToTree(11, arr);
    int* keys = treeToArrayDFS(root);
    printf("tree size: %d\n", treeSize(root));
    for (int i = 0; i < treeSize(root); i++){
        printf("%d\t", keys[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}