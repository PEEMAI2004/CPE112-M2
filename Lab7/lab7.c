// Kamin Jittapassorn 66070503409

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// AVL tree

// Operations: RR, LL, RL, LR, insert, delete, print

// Node structure
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Function prototypes
Node *insert(Node *node, int data);
Node *deleteNode(Node *root, int data);
void print(Node *root);
Node *balance(Node *node); // Function to balance the tree
Node *fixTree(Node *root); // Function to fix unbalanced tree

// Function to get the height of a node
int height(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to create a new node with given data
Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return (node);
}

// Function to right rotate subtree rooted with y
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

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

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to insert a node
Node *insert(Node *node, int data)
{
    // Perform the normal BST insertion
    if (node == NULL)
    {
        return (newNode(data));
    }

    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else
    {
        return node; // Equal keys are not allowed in BST
    }

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the tree
    return balance(node);
}

// Function to balance the tree
Node *balance(Node *node)
{
    // Get the balance factor of this node
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
    {
        return rightRotate(node);
    }

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
    {
        return leftRotate(node);
    }

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to check if a node exists
int exists(Node *root, int data)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->data == data)
    {
        return 1;
    }
    if (data < root->data)
    {
        return exists(root->left, data);
    }
    else
    {
        return exists(root->right, data);
    }
}

// Function to delete a node
Node *deleteNode(Node *root, int data)
{
    // Perform standard BST delete
    if (root == NULL)
    {
        printf("Node not found.\n");
        return root;
    }

    // check if the node exists
    if (!exists(root, data))
    {
        printf("Node not found.\n");
        return root;
    }

    // If the data to be deleted is smaller than the root's data, then it lies in left subtree
    if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }

    // If the data to be deleted is greater than the root's data, then it lies in right subtree
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }

    // If the data is same as root's data, then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            {
                *root = *temp; // Copy the contents of the non-empty child
            }
            free(temp);
        }
        else
        {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node *temp = root->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
    {
        return root;
    }

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Balance the tree
    return balance(root);
}

// Function to print the tree in preorder traversal
void printNode(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        printNode(root->left);
        printNode(root->right);
    }
}

// Functio to check if the tree is empty before printing
void print(Node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty.");
    }
    else
    {
        // fix the tree before printing
        root = fixTree(root);
        printNode(root);
    }
}

// Function to check if the tree is balanced
int isBalanced(Node *root)
{
    int lh; // Height of left subtree
    int rh; // Height of right subtree

    // If tree is empty then return true
    if (root == NULL)
    {
        return 1;
    }

    // Get the height of left and right sub trees
    lh = height(root->left);
    rh = height(root->right);

    if (abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
    {
        return 1;
    }

    // If we reach here then tree is not height-balanced
    return 0;
}

// function to fix unbalanced tree
Node *fixTree(Node *root)
{
    if (root == NULL)
    {
        return root;
    }
    if (isBalanced(root))
    {
        return root;
    }
    else
    {
        return balance(root);
    }
}

// Main function
int main()
{
    Node *root = NULL;
    char option[10];
    int data;
    int flag = 0;

    while (1)
    {
        if (flag == 0)
        {
            scanf("%s", option);
        }
        flag = 0;

        if (strcmp(option, "INSERT") == 0)
        {
            while (1)
            {
                scanf("%s", option);
                // check if the input is a number
                int isNumber = 1;
                int i;
                for (i = 0; i < strlen(option); i++)
                {
                    if (!isdigit(option[i]))
                    {
                        isNumber = 0;
                        break;
                    }
                }
                if (isNumber)
                {
                    data = atoi(option);
                    root = insert(root, data);
                }
                else
                {
                    break;
                }
            }
            flag = 1;
            continue;
        }
        else if (strcmp(option, "DELETE") == 0)
        {
            while (1)
            {
                scanf("%s", option);
                // check if the input is a number
                int isNumber = 1;
                int i;
                for (i = 0; i < strlen(option); i++)
                {
                    if (!isdigit(option[i]))
                    {
                        isNumber = 0;
                        break;
                    }
                }
                if (isNumber)
                {
                    data = atoi(option);
                    root = deleteNode(root, data);
                }
                else
                {
                    break;
                }
            }
            flag = 1;
            continue;
        }
        if (strcmp(option, "PRINT") == 0)
        {
            print(root);
            printf("\n");
        }
        else if (strcmp(option, "EXIT") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Command.\n");
        }
    }
    return 0;
}