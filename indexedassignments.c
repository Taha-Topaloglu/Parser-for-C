
#include "indexedassignments.h"
#include "datastructures.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "infixtopostfix.h"
#include "expressionparsing.h"
#include "stringutils.h"
int isIndexedMatrixAssignment(char* line) {
    char copiedLine[1024];
    strcpy(copiedLine, line);
    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    if (getLinkedListSize(head) < 8)
        return 0;
    char *identifier = getNodeData(head, 0);
    if (!isVariableMatrix(identifier))
        return 0;
    if (strcmp(getNodeData(head, 1), "[") != 0)
        return 0;
    int commaIndex = -1;
    int rightBraceIndex = -1;
    for (int i = 2; i < getLinkedListSize(head); i++) {
        if (strcmp(getNodeData(head,i),",") == 0) {
            commaIndex = i;
        }
        if (strcmp(getNodeData(head, i), "]") == 0) {
            rightBraceIndex = i;
            break;
        }
    }
    if (commaIndex == -1 || rightBraceIndex == -1) {
        return 0;
    }
    if (strcmp(getNodeData(head, rightBraceIndex + 1), "=") != 0) {
        return 0;
    }
    return 1;
}
int isIndexedVectorAssignment(char *line) {

    char copiedLine[1024];
    strcpy(copiedLine, line);
    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    if (getLinkedListSize(head) < 6)
        return 0;
    char *identifier = getNodeData(head, 0);
    if (!isVariableVector(identifier))
        return 0;
    if (strcmp(getNodeData(head, 1), "[") != 0)
        return 0;
    int rightBraceIndex = -1;
    for (int i = 2; i < getLinkedListSize(head); i++) {
        if (strcmp(getNodeData(head, i), "]") == 0) {
            rightBraceIndex = i;
            break;
        }
    }
    if (rightBraceIndex == -1)
        return 0;
    if (strcmp(getNodeData(head, rightBraceIndex + 1), "=") != 0) {
        return 0;
    }
    return 1;
}

int parseIndexedVectorAssignment(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 0);
    char *expression = malloc(1024);
    expression[0] = 0;
    int index = 2;
    while (1) {
        if (strcmp(getNodeData(head, index), "]") == 0) {
            break;
        }
        strcat(expression, getNodeData(head, index));
        index++;
    }

    struct node_for_dll *pNodeForDll = NULL;
    char *deblankedExpr = deblank(expression);
    char *indexResult;
    if (expressionParsing(deblankedExpr, &pNodeForDll)) {
        if (pNodeForDll->is_scalar != 1) {
            return 0;
        }
        indexResult = pNodeForDll->data;
    }
    char *expression2 = malloc(1024);
    expression2[0] = 0;
    for (int i = index + 2; i < getLinkedListSize(head); i++) {
        strcat(expression2, getNodeData(head, i));
    }
    char *deblankedExpr2 = deblank(expression2);
    struct node_for_dll *pNodeForDll2 = NULL;
    char *result;
    if (expressionParsing(deblankedExpr2, &pNodeForDll2)) {
        if (pNodeForDll2->is_scalar != 1) {
            return 0;
        }
        result = pNodeForDll2->data;
    }

    fprintf(file,"%s[%s-1]=%s;\n",identifier,indexResult, result);

    return 1;
}

int parseIndexedMatrixAssignment(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 0);
    char *expression = malloc(1024);
    expression[0] = 0;
    int index = 2;
    while (1) {
        if (strcmp(getNodeData(head, index), ",") == 0) {
            break;
        }
        strcat(expression, getNodeData(head, index));
        index++;
    }
    index++;
    struct node_for_dll *pNodeForDll = NULL;
    char *deblankedExpr = deblank(expression);
    char *indexResult;
    if (expressionParsing(deblankedExpr, &pNodeForDll)) {
        if (pNodeForDll->is_scalar != 1) {
            return 0;
        }
        indexResult = pNodeForDll->data;
    }
    char *rightExpression = malloc(1024);
    rightExpression[0] = 0;
    while (1) {
        if (strcmp(getNodeData(head, index),"]") == 0) {
            break;
        }
        strcat(rightExpression, getNodeData(head, index));
        index++;
    }
    struct node_for_dll *pNodeForDll2 = NULL;
    char *deblankedExpr2 = deblank(rightExpression);
    char *indexResult2;
    if (expressionParsing(deblankedExpr2, &pNodeForDll2)) {
        if (pNodeForDll2->is_scalar != 1) {
            return 0;
        }
        indexResult2 = pNodeForDll2->data;
    }

    char *expression3 = malloc(1024);
    expression3[0] = 0;
    for (int i = index + 2; i < getLinkedListSize(head); i++) {
        strcat(expression3, getNodeData(head, i));
    }
    char *deblankedExpr3 = deblank(expression3);
    struct node_for_dll *pNodeForDll3 = NULL;
    char *result;
    if (expressionParsing(deblankedExpr3, &pNodeForDll3)) {
        if (pNodeForDll3->is_scalar != 1) {
            return 0;
        }
        result = pNodeForDll3->data;
    }

    fprintf(file,"%s[%s-1,%s-1] = %s;\n", identifier, indexResult, indexResult2, result);

    return 1;
}

