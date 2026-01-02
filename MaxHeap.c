#include <stdio.h>

#define MAX 100

int heap[MAX];
int size = 0;

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert into Max Heap
void insertMax(int value) {
    int i = size++;
    heap[i] = value;

    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Heapify for Max Heap
void maxHeapify(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest])
        maxHeapify(largest);
    }
}

// Remove max element
int extractMax() {
    int root = heap[0];
    heap[0] = heap[--size];
    maxHeapify(0);
    return root;
}

int main() {
    insertMax(10);
    insertMax(30);
    insertMax(20);
    insertMax(80);


    printf("Max: %d\n", extractMax());
    return 0;
}

