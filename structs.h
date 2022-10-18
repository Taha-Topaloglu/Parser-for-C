

#ifndef MATLANGPROJECT_STRUCTS_H
#define MATLANGPROJECT_STRUCTS_H


struct Vector {
    char *id;
    int size;
};

struct Scalar {
    char *id;
};

struct Matrix {
    char *id;
    int rowSize;
    int columnSize;
};

/**
 * Append given matrix to the matrices array
 * @param matrix matrix to append
 */
void appendToMatrices(struct Matrix *matrix);

/**
 * append given scalar to scalars array
 * @param scalar scalar to append
 */
void appendToScalars(struct Scalar *scalar);

/**
 * Append given vector to the vector arrays
 * @param vector vector to add
 */
void appendToVectors(struct Vector *vector);

/**
 * check if variable name is already used
 * @param identifier name to check for
 * @return 1 if already used 0 otherwise
 */
int isVariableNameAlreadyUsed(char *identifier);

int isVariableMatrix(char *identifier);

int isVariableVector(char *identifier);

int isVariableScalar(char *identifier);

/**
 * return Matrix pointer with id lexeme identifier
 * @param lexemeIdentifier the id
 * @return the matrix pointer
 */
struct Matrix *findMatrixById(char *lexemeIdentifier);

/**
 * Return the vector pointer with the id
 * @param lexemeIdentifier
 * @return
 */
struct Vector *findVectorById(char *lexemeIdentifier);

struct Scalar *findScalarById(char *identifier);

/**
 * this method is implemented for testing purposes.
 * @return
 */
void printArraySizes();

#endif //MATLANGPROJECT_STRUCTS_H
