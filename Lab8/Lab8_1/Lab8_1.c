// Kamin Jittapassorn 66070503409
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct heap
{
    int *arr, capacity, size;
} heap;

// Function prototypes
heap *createHeap(int capacity);
void insert(heap *Heap, int value);
void delete(heap *Heap, int value);
void printHeap(heap *Heap);
void swap(int *a, int *b);
void heapify(heap *Heap, int index);

// Function to create a heap
heap *createHeap(int capacity)
{
    heap *H = (heap *)malloc(sizeof(heap));
    H->arr = (int *)malloc(capacity * sizeof(int));
    H->size = 0;
    H->capacity = capacity;
    return H;
}

// Function to insert a new element to the heap
void insert(heap *Heap, int value)
{
    if (Heap->size == Heap->capacity) // full
    {
        return; // Return if the heap is full
    }

    int i = Heap->size++; // Increase the size of the heap
    Heap->arr[i] = value; // Insert the new element at the end

    while (i != 0 && Heap->arr[(i - 1) / 2] > Heap->arr[i]) // Fix the min heap property
    {
        swap(&Heap->arr[i], &Heap->arr[(i - 1) / 2]); // Swap the element with its parent
        i = (i - 1) / 2;                              // Update the index of the element
    }
}

// Function to delete an element from the heap
void delete(heap *Heap, int value)
{
    if (Heap->size == 0) // empty
    {
        return;
    }

    int i = 0;
    while (Heap->arr[i] != value) // Find the index of the element to be deleted
    {
        i++;
    }
    swap(&Heap->arr[i], &Heap->arr[Heap->size - 1]); // Swap the element with the last element
    Heap->size--;                                    // Decrease the size of the heap

    for (int i = (Heap->size / 2) - 1; i >= 0; i--) // Heapify the heap
    {
        heapify(Heap, i);
    }
}

// Function to print the heap
void printHeap(heap *Heap)
{
    for (int i = 0; i < Heap->size; i++)
    {
        printf("%d ", Heap->arr[i]);
    }
    printf("\n");
}

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

// Function to heapify the heap
void heapify(heap *Heap, int index)
{
    int smallest = index;      // Initialize smallest as root
    int left = 2 * index + 1;  // left = 2*i + 1
    int right = 2 * index + 2; // right = 2*i + 2

    if (left < Heap->size && Heap->arr[left] < Heap->arr[smallest])
        smallest = left; // If left child is smaller than root

    if (right < Heap->size && Heap->arr[right] < Heap->arr[smallest])
        smallest = right; // If right child is smaller than root

    if (smallest != index) // If smallest is not root
    {
        swap(&Heap->arr[index], &Heap->arr[smallest]);
        heapify(Heap, smallest); // Recursively heapify the affected sub-tree
    }
}

int main()
{
    heap *Heap = createHeap(128);
    char command[8];
    int temp;
    do
    {
        scanf("%s", command);
        if (strcmp(command, "INSERT") == 0)
        {
            while (scanf("%d", &temp))
            {
                insert(Heap, temp);
            }
        }
        else if (strcmp(command, "DELETE") == 0)
        {
            while (scanf("%d", &temp))
            {
                delete (Heap, temp);
            }
        }
        else if (strcmp(command, "PRINT") == 0)
        {
            printHeap(Heap);
        }
        else if (strcmp(command, "EXIT") == 0)
        {
            free(Heap);
            return 0;
        }
        else
        {
            printf("Invalid command.\n");
            continue;
        }
    } while (1);

    return 0;
}