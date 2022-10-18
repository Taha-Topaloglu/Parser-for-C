

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "printstatements.h"
#include "datastructures.h"
#include "structs.h"
#include "stringutils.h"
#include "expressionparsing.h"

int isUsualPrintIdStatement(char *line) {
    char *cpy = strdup(line);
    char *temp = strtok(cpy, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }

    if (getLinkedListSize(head) != 4)
        return 0;
    if (strcmp(getNodeData(head, 0), "print") != 0)
        return 0;
    if (strcmp(getNodeData(head, 1), "(") != 0)
        return 0;
    char *identifier = getNodeData(head, 2);
    if (!isVariableNameAlreadyUsed(identifier))
        return 0;
    if (strcmp(getNodeData(head, 3), ")") != 0)
        return 0;

    return 1;
}

int isPrintIdWithIndex(char *line) {
    char *cpy = strdup(line);
    char *temp = strtok(cpy, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    if (getLinkedListSize(head) < 7)
        return 0;
    if (strcmp(getNodeData(head, 0), "print") != 0)
        return 0;
    if (strcmp(getNodeData(head, 1), "(") != 0)
        return 0;
    char *identifier = getNodeData(head, 2);
    if (!isVariableNameAlreadyUsed(identifier) && !isVariableScalar(identifier))
        return 0;
    if (strcmp(getNodeData(head, getLinkedListSize(head) - 1), ")") != 0) {
        return 0;
    }
    return 1;
}

int parsePrintIdWithIndex(char *line, FILE* file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 2);
    if (isVariableVector(identifier)) {
        if (strcmp(getNodeData(head, 3), "[") != 0)
            return 0;
        char *expression = malloc(1024);
        expression[0] = 0;
        int rightBraceIndex = -1;
        for (int i = 4; i < getLinkedListSize(head); i++) {
            if (strcmp(getNodeData(head, i), "]") == 0) {
                rightBraceIndex = i;
                break;
            }
        }
        if (rightBraceIndex == -1)
            return 0;
        for (int i = 4; i < rightBraceIndex; i++) {
            strcat(expression, getNodeData(head, i));
        }
        char *deblankedExpr = deblank(expression);
        struct node_for_dll *pNodeForDll = NULL;
        char *indexResult;
        if (expressionParsing(deblankedExpr, &pNodeForDll)) {
            if (pNodeForDll->is_scalar != 1)
                return 0;
            indexResult = pNodeForDll->data;
            fprintf(file,"customPrint(%s[%s-1]);\n", identifier, indexResult);
            return 1;
        } else {
            return 0;
        }
    } else {

        if (strcmp(getNodeData(head, 3), "[") != 0)
            return 0;
        char *expressionLeft = malloc(1024);
        expressionLeft[0] = 0;
        char *expressionRight = malloc(1024);
        expressionRight[0] = 0;

        int rightBraceIndex = -1;
        int commaIndex = -1;
        for (int i = 4; i < getLinkedListSize(head); i++) {
            if (strcmp(getNodeData(head, i), ",") == 0 && commaIndex == -1) {
                commaIndex = i;
                continue;
            }
            if (strcmp(getNodeData(head, i), "]") == 0 && commaIndex != -1) {
                rightBraceIndex = i;
                break;
            }
        }
        if (commaIndex == -1 || rightBraceIndex == -1 || commaIndex > rightBraceIndex)
            return 0;
        for (int i = 4; i < commaIndex; i++) {
            strcat(expressionLeft, getNodeData(head, i));
        }
        for (int i = commaIndex + 1; i < rightBraceIndex; i++) {
            strcat(expressionRight, getNodeData(head, i));
        }
        char *deblankedExprLeft = deblank(expressionLeft);
        struct node_for_dll *pNodeForDll = NULL;
        char *indexResultLeft;
        if (expressionParsing(deblankedExprLeft, &pNodeForDll)) {
            if (pNodeForDll->is_scalar != 1)
                return 0;
            indexResultLeft = pNodeForDll->data;
        } else {
            return 0;
        }
        char *deblankedExprRight = deblank(expressionRight);
        struct node_for_dll *pNodeForDll2 = NULL;
        char *indexResultRight;
        if (expressionParsing(deblankedExprRight, &pNodeForDll2)) {
            if (pNodeForDll2->is_scalar != 1)
                return 0;
            indexResultRight = pNodeForDll2->data;
        } else {
            return 0;
        }

        printf("customPrint(%s[%s-1,%s-1]);\n\n", identifier, indexResultLeft, indexResultRight);
        return 1;
    }


}

int isPrintSepStatement(char *line) {
    char *cpy = strdup(line);
    char *temp = strtok(cpy, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    if (getLinkedListSize(head) != 3)
        return 0;
    if (strcmp(getNodeData(head, 0), "printsep") != 0)
        return 0;
    if (strcmp(getNodeData(head, 1), "(") != 0)
        return 0;
    if (strcmp(getNodeData(head, 2), ")") != 0)
        return 0;

    return 1;
}

int parseUsualPrintIdStatement(char *line, FILE *file) {
    char *temp = strtok(line, " \n");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, " \n");
        appendToLinkedList(head, temp);
    }
    char *identifier = getNodeData(head, 2);
    if (isVariableScalar(identifier)) {
        struct Scalar *scalar = findScalarById(identifier);
        fprintf(file, "customPrint(%s);", scalar->id);
        fprintf(file, "\n");
        return 1;
    }
    if (isVariableVector(identifier)) {
        struct Vector *vector = findVectorById(identifier);
        char *code = "for (int i = 0; i < %d; i++) {\n\tcustomPrint(%s[i]);\n}\n";
        fprintf(file, code, vector->size, vector->id);
        return 1;
    }
    if (isVariableMatrix(identifier)) {
        struct Matrix *matrix = findMatrixById(identifier);
        char *code = "for (int i = 0; i < %d; i++) {\n\tfor (int j = 0; j < %d; j++) "
                     "{\n\t\tcustomPrint(%s[i][j]);\n\t}\n}\n";
        fprintf(file, code, matrix->rowSize, matrix->columnSize, matrix->id);
        return 1;
    }
    return 0;
}

int parsePrintSepStatement(char *line, FILE *file) {
    fprintf(file, "printf(\"------------\\n\");\n");
    return 1;
}