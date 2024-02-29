// Kamin Jittapassorn 66070503409
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createRoot(int tree[], int val)
{
    int index = 1;
    if (tree[index] != -1)
    {
        printf("cannot create duplicated root\n");
    }
    else
    {
        tree[index] = val;
        index++;
    }
}

void insertLeftChild(int tree[], int parent, int val, int size)
{
    int i = 1, flag = 0;
    while (i <= size)
    {
        if (tree[i] == parent)
        {
            flag = 1;
            break;
        }
        i++;
    }
    if (flag == 0)
    {
        printf("not found\n"); // not found
    }
    else if (i * 2 > size)
    {
        printf("overflow\n");
    }
    else if (tree[2 * i] != -1)
    {
        printf("node already presented\n");
    }
    else if (tree[2 * i] == -1)
    {
        tree[2 * i] = val;
    }
}

void insertRightChild(int tree[], int parent, int val, int size)
{
    int i = 1, flag = 0;
    while (i <= size)
    {
        if (tree[i] == parent)
        {
            flag = 1;
            break;
        }
        i++;
    }
    if (flag == 0)
    {
        printf("not found\n"); // not found
    }
    else if (2 * i + 1 > size)
    {
        printf("overflow\n");
    }
    else if (tree[2 * i + 1] == -1)
    {
        tree[(2 * i) + 1] = val;
    }
    else if (tree[2 * i + 1] != -1)
    {
        printf("node already presented\n");
    }
}

void printTree(int tree[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        if (tree[i] == -1)
        {
            printf("null ");
        }
        else
        {
            printf("%d ", tree[i]);
        }
    }
}

int main()
{
    int size;
    scanf("%d", &size);
    // create tree with size + 1
    int *tree = (int *)malloc((size + 1) * sizeof(int));
    // init to -1 as in NULL
    for (int i = 0; i <= size; i++)
    {
        tree[i] = -1;
    }
    char mode[5];
    do
    {
        scanf("%s", mode);
        if (strcmp(mode, "ROOT") == 0)
        {
            int val;
            scanf("%d", &val);
            createRoot(tree, val);
        }
        else if (strcmp(mode, "INSL") == 0)
        {
            int par, val;
            scanf("%d%d", &par, &val);
            insertLeftChild(tree, par, val, size);
        }
        else if (strcmp(mode, "INSR") == 0)
        {
            int par, val;
            scanf("%d%d", &par, &val);
            insertRightChild(tree, par, val, size);
        }
        else if (strcmp(mode, "END") == 0)
        {
            printTree(tree, size);
            break;
        }
        else
        {
            continue;
        }
    } while (strcmp(mode, "END") != 0);

    return 0;
}

