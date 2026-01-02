#include <stdio.h>

#define MAX 100

// Diziyi yazdırma
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Belirli indekse ekleme
int insert(int arr[], int size, int element, int index) {
    int i;

    if (size >= MAX) {
        printf("Dizi dolu!\n");
        return size;
    }

    for (i = size; i > index; i--)
        arr[i] = arr[i - 1];

    arr[index] = element;
    return size + 1;
}

// Belirli indeksten silme
int delete(int arr[], int size, int index) {
    int i;

    if (index >= size) {
        printf("Gecersiz indeks!\n");
        return size;
    }

    for (i = index; i < size - 1; i++)
        arr[i] = arr[i + 1];

    return size - 1;
}

int main() {
    int arr[MAX] = {10, 20, 30, 40, 50};
    int size = 5;

    printf("Ilk dizi: ");
    printArray(arr, size);

    // Ekleme
    size = insert(arr, size, 25, 2);
    printf("Ekledikten sonra: ");
    printArray(arr, size);

    // Silme
    size = delete(arr, size, 3);
    printf("Sildikten sonra: ");
    printArray(arr, size);

    return 0;
}
