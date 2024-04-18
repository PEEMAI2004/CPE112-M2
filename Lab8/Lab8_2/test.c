#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to right rotate subtree rooted with y
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Return new root
    return y;
}

// Function to get balance factor of a node
int getBalance(Node *node){
    if (node == NULL){
        return 0;}
    return height(node->left) - height(node->right);}

// Function to insert a node
Node *insert(Node *node, int data){
    // Perform the normal BST insertion
    if (node == NULL){
        return (newNode(data));}
    if (data < node->data){
        node->left = insert(node->left, data);}
    else if (data > node->data){
        node->right = insert(node->right, data);}
    else{ // Equal keys are not allowed in BST
        return node;}
    return balance(node);// Balance the tree
}

Node *balance(Node *node){
    // Get the balance factor of this node
    int balance = getBalance(node);
    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0){
        return rightRotate(node);}
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0){
        node->left = leftRotate(node->left);
        return rightRotate(node);}
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0){
        return leftRotate(node);}
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0){
        node->right = rightRotate(node->right);
        return leftRotate(node);}
    // Return the (unchanged) node pointer
    return node;}

// Function to delete a node
Node *deleteNode(Node *root, int data){
    // Perform standard BST delete
    if (root == NULL){
        printf("Node not found.\n");
        return root;}
    // check if the node exists
    if (!exists(root, data)){
        printf("Node not found.\n");
        return root;}
    // If the data to be deleted is smaller than the root's data
    if (data < root->data){
        root->left = deleteNode(root->left, data);}
    // If the data to be deleted is greater than the root's data
    else if (data > root->data){
        root->right = deleteNode(root->right, data);}
    // If the data is same as root's data, then this is the node to be deleted
    else{
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)){
            Node *temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL){
                temp = root;
                root = NULL;}
            else { // One child case
                *root = *temp; }// Copy the contents of the non-empty child
            free(temp);}
        else{
            // Node with two children: Get the inorder successor 
            // (smallest in the right subtree)
            Node *temp = root->right;
            while (temp->left != NULL){
                temp = temp->left;}
            // Copy the inorder successor's data to this node
            root->data = temp->data;
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);}}
    if (root == NULL){ // If the tree had only one node then return
        return root;}
    return balance(root); // Balance the tree
}

// Function to print the tree in preorder traversal
void printNode(Node *root){
    if (root != NULL){
        printf("%d ", root->data);
        printNode(root->left);
        printNode(root->right);}}
