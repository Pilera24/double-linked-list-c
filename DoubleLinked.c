#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};
void traverse(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
void insertAfter(struct Node* head, int after, int value) {
    struct Node* temp = head;

    while (temp != NULL && temp->data != after)
        temp = temp->next;

    if (temp == NULL) {
        printf("Eleman bulunamadi\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;
}struct Node* deleteNode(struct Node* head, int value) {
    struct Node* temp = head;

    while (temp != NULL && temp->data != value)
        temp = temp->next;

    if (temp == NULL) {
        printf("Eleman bulunamadi\n");
        return head;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;   // baş siliniyorsa

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    return head;
}
int main() {
    struct Node* head = NULL;

    // İlk node
    head = (struct Node*)malloc(sizeof(struct Node));
    head->data = 10;
    head->prev = NULL;
    head->next = NULL;

    // İkinci node
    struct Node* second = (struct Node*)malloc(sizeof(struct Node));
    second->data = 20;
    second->prev = head;
    second->next = NULL;
    head->next = second;

    traverse(head);

    insertAfter(head, 10, 15);
    traverse(head);

    head = deleteNode(head, 20);
    traverse(head);

    return 0;
}

