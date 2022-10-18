

#ifndef MATLANGPROJECT_DATASTRUCTURES_H
#define MATLANGPROJECT_DATASTRUCTURES_H
struct Node {
    struct Node *next;
    char* data;
};

/**
 * append to end of a linked list
 * @param head
 */
void appendToLinkedList(struct Node* head, char* data);

/**
 * Create a new Node with given data in HEAP
 * @param data
 * @return pointer to the node
 */
struct Node* createNode(char* data);

/**
 * Get the data of the node with the given index
 * @param index index of node, index starts from 0
 * @return data
 */
char* getNodeData(struct Node* head, int index);

/**
 *
 * @param head the linked list
 * @return size of the linked list
 */
int getLinkedListSize(struct Node* head);
#endif //MATLANGPROJECT_DATASTRUCTURES_H
