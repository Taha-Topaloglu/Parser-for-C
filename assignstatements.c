

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "assignstatements.h"
#include "structs.h"
#include "stringutils.h"
#include "datastructures.h"
#include "expressionparsing.h"
#include "infixtopostfix.h"

int parseVectorAssignmentWithExpression(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);

    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }

    char *identifier = getNodeData(head, 0);
    struct node_for_dll *nodeForDll = NULL;
    char *expression = malloc(1024);
    expression[0] = 0;
    for (int i = 2; i < getLinkedListSize(head); i++) {
        strcat(expression, getNodeData(head, i));
    }

    char *deblankedExpr = deblank(expression);
    if (expressionParsing(deblankedExpr, &nodeForDll)) {
        if (nodeForDll->size == findVectorById(identifier)->size) {
            char *code = "for (int __i = 0; __i < %d; __i++) {\n"
                         "                %s[__i] = %s[__i];\n"
                         "            }\n";
            fprintf(file, code, nodeForDll->size, identifier, nodeForDll->data);
            return 1;
        } else if (nodeForDll->row_size == findVectorById(identifier)->size &&
                   nodeForDll->column_size == 1) {
            char *code = "    for (int _i = 0; _i < %d; _i++) {\n"
                         "        %s[_i] = %s[_i][0];\n"
                         "    }\n";
            fprintf(file, code, nodeForDll->row_size, identifier, nodeForDll->data);
            return 1;
        }
    }

    return 0;
}

int isVectorAssignmentWithExpression(char *line) {
    char copiedLine[256];
    strcpy(copiedLine, line);

    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 0);
    if (getLinkedListSize(head) <= 2) {
        return 0;
    }
    char *token = getNodeData(head, 1);
    if (isVariableVector(identifier) == 1 && strcmp(token, "=") == 0)
        return 1;
    else
        return 0;
}

int isUsualVectorAssignment(char *line) {
    char copiedLine[256];
    strcpy(copiedLine, line);

    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 0);
    if (getLinkedListSize(head) <= 2) {
        return 0;
    }
    char *token = getNodeData(head, 1);
    if (isVariableVector(identifier) == 1 && strcmp(token, "=") == 0 && strcmp(getNodeData(head, 2), "{") == 0)
        return 1;
    else
        return 0;
}

int isScalarAssignment(char *line) {
    char copiedLine[1024];
    strcpy(copiedLine, line);
    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }

    if (getLinkedListSize(head) <= 2)
        return 0;
    char *identifier = getNodeData(head, 0);
    char *token = getNodeData(head, 1);
    if (isVariableScalar(identifier) && strcmp(token, "=") == 0) {
        return 1;
    } else
        return 0;
}

int isMatrixAssignmentWithExpression(char *line) {
    char copiedLine[256];
    strcpy(copiedLine, line);

    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 0);
    if (getLinkedListSize(head) <= 2) {
        return 0;
    }
    char *token = getNodeData(head, 1);
    if (isVariableMatrix(identifier) == 1 && strcmp(token, "=") == 0)
        return 1;
    else
        return 0;
}

int parseMatrixAssignmentWithExpression(char *line, FILE *out) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);

    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }

    char *identifier = getNodeData(head, 0);
    struct node_for_dll *nodeForDll = NULL;
    char *expression = malloc(1024);
    expression[0] = 0;
    for (int i = 2; i < getLinkedListSize(head); i++) {
        strcat(expression, getNodeData(head, i));
    }

    char *deblankedExpr = deblank(expression);
    if (expressionParsing(deblankedExpr, &nodeForDll)) {
        if (nodeForDll->row_size == findMatrixById(identifier)->rowSize &&
            nodeForDll->column_size == findMatrixById(identifier)->columnSize) {
            fprintf(out, "%s = %s;\n", identifier, nodeForDll->data);
            return 1;
        }
    }
    return 0;
}

int isUsualMatrixAssignment(char *line) {
    char copiedLine[256];
    strcpy(copiedLine, line);
    char *temp = strtok(copiedLine, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    if (getLinkedListSize(head) <= 2) {
        return 0;
    }
    char *identifier = getNodeData(head, 0);
    char *token = getNodeData(head, 1);

    if (isVariableMatrix(identifier) && (strcmp(token, "=") == 0) && strcmp(getNodeData(head, 2), "{") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int parseUsualMatrixAssignment(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);

    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }

    char *identifier = getNodeData(head, 0);
    struct Matrix *matrix = findMatrixById(identifier);

    int expectedSize = 4 + matrix->columnSize * matrix->rowSize;
    if (getLinkedListSize(head) != expectedSize) {
        printf("ERROR PARSING MATRIX ASSIGNMENT!\n");
        return 0;
    }

    if (strcmp(getNodeData(head, 1), "=") != 0) {
        printf("MISSING =\n");
        return 0;
    }

    if (strcmp(getNodeData(head, 2), "{") != 0) {
        printf("MISSING LEFT BRACKET\n");
        return 0;
    }

    for (int i = 3; i < expectedSize - 1; i++) {
        if (!isFloat(getNodeData(head, i))) {
            printf("ELEMENT NOT NUMBER\n");
            return 0;
        }
    }

    if (strcmp(getNodeData(head, getLinkedListSize(head) - 1), "}") != 0) {
        printf("MISSING RIGHT BRACKET!\n");
        return 0;
    }


    int index = 3;
    for (int i = 0; i < matrix->rowSize; i++) {
        for (int j = 0; j < matrix->columnSize; j++) {
            double value = strtod(getNodeData(head, index), NULL);
            fprintf(file, "%s[%d][%d] = %f;\n", matrix->id, i, j, value);
            index++;
        }
    }


    return 1;
}

int parseScalarAssignment(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);

    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 0);
    struct node_for_dll *nodeForDll = NULL;
    char *expression = malloc(1024);
    expression[0] = 0;
    for (int i = 2; i < getLinkedListSize(head); i++) {
        strcat(expression, getNodeData(head, i));
    }

    char *deblankedExpr = deblank(expression);
    if (expressionParsing(deblankedExpr, &nodeForDll)) {
        if (nodeForDll->is_scalar == 1) {
            fprintf(file, "%s = %s;\n", identifier, nodeForDll->data);
            return 1;
        } else if (nodeForDll->is_matrix == 1 && nodeForDll->column_size == 1 && nodeForDll->row_size == 1) {
            fprintf(file, "%s = %s[0][0];\n", identifier, nodeForDll->data);
            return 1;
        }
    }

    return 0;

}

int parseUsualVectorAssignment(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);

    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }

    char *identifier = getNodeData(head, 0);
    struct Vector *vector = findVectorById(identifier);
    int expectedSize = 4 + vector->size;
    if (getLinkedListSize(head) != expectedSize) {
        printf("ERROR PARSING VECTOR ASSIGNMENT\n");
        return 0;
    }
    if (strcmp(getNodeData(head, 2), "{") != 0) {
        printf("MISSING LEFT BRACE!");
        return 0;
    }

    for (int i = 3; i < expectedSize - 1; i++) {
        if (!isFloat(getNodeData(head, i))) {
            printf("ELEMENT NOT NUMBER!\n");
            return 0;
        }
    }

    if (strcmp(getNodeData(head, getLinkedListSize(head) - 1), "}") != 0) {
        printf("MISSING RIGHT BRACKET\n");
        return 0;
    }
    int valueIndex = 3;
    for (int i = 0; i < vector->size; i++) {
        double value = strtod(getNodeData(head, valueIndex), NULL);
        fprintf(file, "%s[%d] = %f;\n", identifier, i, value);
        valueIndex++;
    }


    return 1;
}

