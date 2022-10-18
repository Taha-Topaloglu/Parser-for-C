#include <stdio.h>
#include <string.h>
#include "structs.h"

struct Vector *vectors[1024];
struct Scalar *scalars[1024];
struct Matrix *matrices[1024];
int vectorArraySize = 0;
int matrixArraySize = 0;
int scalarArraySize = 0;

void appendToVectors(struct Vector *vector) {
    vectors[vectorArraySize] = vector;
    vectorArraySize++;
}

void appendToMatrices(struct Matrix *matrix) {
    matrices[matrixArraySize] = matrix;
    matrixArraySize++;
}

void appendToScalars(struct Scalar *scalar) {
    scalars[scalarArraySize] = scalar;
    scalarArraySize++;
}

void printArraySizes() {
    printf("MATRIX %d SCALAR %d VECTOR %d\n", matrixArraySize, scalarArraySize, vectorArraySize);
}

int isVariableNameAlreadyUsed(char *identifier) {
    for (int i = 0; i < scalarArraySize; i++) {
        if (strcmp(identifier, scalars[i]->id) == 0) {
            return 1;
        }
    }

    for (int i = 0; i < matrixArraySize; i++) {
        if (strcmp(identifier, matrices[i]->id) == 0) {
            return 1;
        }
    }

    for (int i = 0; i < vectorArraySize; ++i) {
        if (strcmp(identifier, vectors[i]->id) == 0) {
            return 1;
        }
    }

    return 0;
}

int isVariableMatrix(char *identifier) {
    for (int i = 0; i < matrixArraySize; i++) {
        if (strcmp(identifier, matrices[i]->id) == 0)
            return 1;
    }
    return 0;
}

int isVariableScalar(char *identifier) {
    for (int i = 0; i < scalarArraySize; i++) {
        if (strcmp(identifier, scalars[i]->id) == 0)
            return 1;
    }
    return 0;
}

int isVariableVector(char *identifier) {
    for (int i = 0; i < vectorArraySize; ++i) {
        if (strcmp(identifier, vectors[i]->id) == 0)
            return 1;
    }
    return 0;
}

struct Matrix *findMatrixById(char *identifier) {
    for (int i = 0; i < matrixArraySize; i++) {
        if (strcmp(identifier, matrices[i]->id) == 0)
            return matrices[i];
    }
    return NULL;
}

struct Vector *findVectorById(char *lexemeIdentifier) {
        for (int i = 0; i < vectorArraySize; ++i) {
        if (strcmp(lexemeIdentifier, vectors[i]->id) == 0)
            return vectors[i];
    }
    return NULL;
}

struct Scalar *findScalarById(char *identifier) {
    for (int i = 0; i < scalarArraySize; i++) {
        if (strcmp(identifier, scalars[i]->id) == 0)
            return scalars[i];
    }
    return NULL;
}
