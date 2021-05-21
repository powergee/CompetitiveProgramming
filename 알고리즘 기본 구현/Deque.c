#include <stdlib.h>

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    void* value;
} Node;

typedef struct {
    Node head;
    int count;
} List;

Node* createNode(void* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    return node;
}

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->count = 0;
    list->head.next = &list->head;
    list->head.prev = &list->head;
    list->head.value = NULL;
    return list;
}

void insertBetween(List* list, Node* prev, Node* next, void* value) {
    Node* newNode = createNode(value);
    prev->next = next->prev = newNode;
    newNode->next = next;
    newNode->prev = prev;
    list->count++;
}

void pushBack(List* list, void* value) {
    Node* prev = list->head.prev;
    Node* next = &list->head;
    insertBetween(list, prev, next, value);
}

void pushFront(List* list, void* value) {
    Node* prev = &list->head;
    Node* next = list->head.next;
    insertBetween(list, prev, next, value);
}

void removeNode(List* list, Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    prev->next = next;
    next->prev = prev;
    free(node);
    list->count--;
}

void* popBack(List* list) {
    void* value = list->head.prev->value;
    removeNode(list, list->head.prev);
    return value;
}

void* popFront(List* list) {
    void* value = list->head.next->value;
    removeNode(list, list->head.next);
    return value;
}

void* getBack(List* list) {
    return list->head.prev->value;
}

void* getFront(List* list) {
    return list->head.next->value;
}