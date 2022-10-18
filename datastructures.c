

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "datastructures.h"

struct Node *createNode(char *data) {
    struct Node *node = malloc(sizeof(struct Node));
    node->next = NULL;
    char* copied = strdup(data);
    node->data = copied;
    return node;
}


void appendToLinkedList(struct Node *head, char* data) {
    if (data == NULL)
        return;
    struct Node* lastNode = head;
    struct Node* nodeToAppend = createNode(data);
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = nodeToAppend;
}

char* getNodeData(struct Node* head, int index) {
    struct Node *node = head;
    while (index > 0) {
        node = node->next;
        index--;
    }
    return node->data;
}

int getLinkedListSize(struct Node* head) {
    struct Node *currentNode = head;
    int count = 0;
    while (currentNode != NULL) {
        count++;
        currentNode = currentNode->next;
    }
    return count;
}
