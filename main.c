#include <stdio.h>
#include "stringutils.h"
#include "definitionstatements.h"
#include "assignstatements.h"
#include "printstatements.h"
#include "expressionparsing.h"
#include "infixtopostfix.h"
#include "indexedassignments.h"
#include "forloops.h"

static int ERROR = 0;
static int LINE_LIMIT = 256;
static int lineCount = 0;
int hasPendingRightBracket = 0;
int canPutRightBracket = 0;
int isDoubleFor = 0;

int parseLine(char *line, FILE *outFile);

void defineFunctions(FILE *out);

void createMain(FILE *out);

int main(int argc, char *argv[]) {
    FILE *fp;
    FILE *out = fopen("file.c", "w");
    char line[LINE_LIMIT];
    /** Open file for reading Filename is given on the command line */
    if (argc != 2) {
        printf("Give filename as command line argument\n");
        return (1);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return (1);
    }

    int errorOccured = 0;
    defineFunctions(out);
    createMain(out);
    while (fgets(line, LINE_LIMIT, fp) != NULL) {
        if (parseLine(line, out) == ERROR) {
            errorOccured = 1;
            fclose(out);
            remove("file.c");
            break;
        }
    }
    if (!errorOccured) {
        if (hasPendingRightBracket) {
            printf("Error (Line %d)\n", lineCount);
            fclose(out);
            remove("file.c");
            return -1;
        } else {
            fprintf(out, "return 0;\n\n}");
        }
    }
    fclose(fp);
    fclose(out);
    return (0);
}

int parseLine(char *line, FILE *outFile) {
    if (isEmptyString(line, LINE_LIMIT)) {
        lineCount++;
        return 1;
    }
    char *strippedLine = strippedString(line, LINE_LIMIT);
    if (isCommentLine(strippedLine)) {
        lineCount++;
        return 1;
    }


    char *spacedLine = getSpacedVersionOf(strippedLine);

    if (isScalarDefinition(spacedLine)) {
        if (parseScalarDefinition(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isMatrixDefinition(spacedLine)) {

        if (parseMatrixDefinition(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isVectorDefinition(spacedLine)) {

        if (parseVectorDefinition(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isUsualVectorAssignment(spacedLine)) {

        if (parseUsualVectorAssignment(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isUsualMatrixAssignment(spacedLine)) {

        if (parseUsualMatrixAssignment(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isMatrixAssignmentWithExpression(spacedLine)) {
        if (parseMatrixAssignmentWithExpression(line, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isVectorAssignmentWithExpression(spacedLine)) {
        if (parseVectorAssignmentWithExpression(line, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isPrintSepStatement(spacedLine)) {

        if (parsePrintSepStatement(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isUsualPrintIdStatement(spacedLine)) {
        if (parseUsualPrintIdStatement(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isScalarAssignment(spacedLine)) {

        if (parseScalarAssignment(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isIndexedVectorAssignment(spacedLine)) {

        if (parseIndexedVectorAssignment(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isIndexedMatrixAssignment(spacedLine)) {

        if (parseIndexedMatrixAssignment(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else if (isSingleForLoop(spacedLine)) {
        if (parseSingleForLoop(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
        hasPendingRightBracket++;
        canPutRightBracket++;
    } else if (strcmp(strippedLine, "}") == 0 || strcmp(strippedLine, "}\n") == 0) {
        if (canPutRightBracket != 1) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
        if (isDoubleFor == 1) {
            fprintf(outFile, "}\n");
            fprintf(outFile, "}\n");
            isDoubleFor = 0;
        } else
            fprintf(outFile, "}\n");
        hasPendingRightBracket--;
        canPutRightBracket--;
    } else if (isDoubleForLoop(spacedLine)) {
        if (parseDoubleForLoop(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
        hasPendingRightBracket++;
        canPutRightBracket++;
        isDoubleFor = 1;
    } else if (isPrintIdWithIndex(spacedLine)) {

        if (parsePrintIdWithIndex(spacedLine, outFile) == ERROR) {
            printf("Error (Line %d)\n", lineCount);
            return 0;
        }
    } else {
        printf("Error (Line %d)\n", lineCount);
        return 0;
    }
    lineCount++;
    return 1;
}

void defineFunctions(FILE *out) {
    fprintf(out, "#include <malloc.h>\n#include<string.h>\n#include<stdio.h>\n#include <math.h>\n\n");
    char *_choose = "int choose(int a , int b , int c , int d)\n"
                    "{\n"
                    "    if(a == 0)\n"
                    "    {\n"
                    "        return b;\n"
                    "    }\n"
                    "    else if(a > 0)\n"
                    "    {\n"
                    "        return c;\n"
                    "    }\n"
                    "\n"
                    "    return d;\n"
                    "}";
    fprintf(out, _choose);

    char* customPrint = "void customPrint(double number) {\n"
                        "    double precision = 0.00000001;\n"
                        "    if (number - (int) number < precision ) {\n"
                        "        int numberInt = (int) number;\n"
                        "        printf(\"%%d\\n\", numberInt);\n"
                        "    } else if ((int) number + 1 - number < precision) {\n"
                        "        int numberInt = (int) number + 1;\n"
                        "        printf(\"%%d\\n\",numberInt);\n"
                        "    } else\n"
                        "        printf(\"%%f\\n\", number);\n"
                        "}\n";
    fprintf(out, customPrint);

    char *_other = "char* convertIntegerToChar(int N)\n"
                   "{\n"
                   "    int m = N;\n"
                   "    int digit = 0;\n"
                   "    while (m) {\n"
                   "\n"
                   "        digit++;\n"
                   "\n"
                   "        m /= 10;\n"
                   "    }\n"
                   "\n"
                   "    char* arr;\n"
                   "\n"
                   "    char arr1[digit];\n"
                   "\n"
                   "    arr = (char*)malloc(digit);\n"
                   "\n"
                   "    int index = 0;\n"
                   "    while (N) {\n"
                   "\n"
                   "        arr1[++index] = N % 10 + '0';\n"
                   "\n"
                   "        N /= 10;\n"
                   "    }\n"
                   "\n"
                   "    int i;\n"
                   "    for (i = 0; i < index; i++) {\n"
                   "        arr[i] = arr1[index - i];\n"
                   "    }\n"
                   "\n"
                   "    arr[i] = '\\0';\n"
                   "\n"
                   "    return (char*)arr;\n"
                   "}\n"
                   "\n"
                   "double **transposeVector(double *vec , int size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = 1;\n"
                   "    int column = size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "\n"
                   "    for (j = 0; j < column; j++) {\n"
                   "        new_mat[0][j] = vec[j];\n"
                   "    }\n"
                   "\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **transposeMatrix(double **mat , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(column * sizeof(double*));\n"
                   "    for (i = 0; i < column; i++)\n"
                   "        new_mat[i] = (double*)malloc(row * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++) {\n"
                   "        for (j = 0; j < column; j++) {\n"
                   "            new_mat[j][i] = mat[i][j];\n"
                   "        }\n"
                   "    }\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "\n"
                   "double *addScalarToVector(double sca , double *vec , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = vec[i] + sca;\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "\n"
                   "}\n"
                   "\n"
                   "double *subtractScalarFromVector(double sca , double *vec , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = vec[i] - sca;\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "}\n"
                   "\n"
                   "double *subtractVectorFromScalar(double sca , double *vec , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = sca - vec[i];\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "}\n"
                   "\n"
                   "double *multiplyScalarWithVector(double sca , double *vec , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = vec[i] * sca;\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "}\n"
                   "\n"
                   "double **addScalarToMatrix(double sca , double **mat , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat[i][j] + sca;\n"
                   "\n"
                   "    return new_mat;\n"
                   "\n"
                   "}\n"
                   "\n"
                   "double **subtractScalarFromMatrix(double sca , double **mat , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat[i][j] - sca;\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **subtractMatrixFromScalar(double sca , double **mat , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = sca - mat[i][j];\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **multiplyScalarWithMatrix(double sca , double **mat , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat[i][j] * sca;\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double *vectorAddition(double *vec1 , double *vec2 , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = vec1[i] + vec2[i];\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "}\n"
                   "\n"
                   "double *vectorSubtraction(double *vec1 , double *vec2 , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = vec1[i] - vec2[i];\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "}\n"
                   "\n"
                   "double *vectorMultiplication(double *vec1 , double *vec2 , int v_size)\n"
                   "{\n"
                   "    int i = 0;\n"
                   "    int size = v_size;\n"
                   "\n"
                   "    double *new_vec = (double*) malloc(size * sizeof(double));\n"
                   "\n"
                   "    for(i = 0 ; i < size ; i++)\n"
                   "    {\n"
                   "        new_vec[i] = vec1[i] * vec2[i];\n"
                   "    }\n"
                   "\n"
                   "    return new_vec;\n"
                   "}\n"
                   "\n"
                   "double **matrixAddition(double **mat1 , double **mat2 , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat1[i][j] + mat2[i][j];\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **matrixSubtraction(double **mat1 , double **mat2  , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat1[i][j] - mat2[i][j];\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **matrixMultiplication(double **mat1 , double **mat2 , int row_size1 , int column_size1 , int row_size2 , int column_size2)\n"
                   "{\n"
                   "    int i = 0 , j = 0 , k = 0;\n"
                   "\n"
                   "    int row1 = row_size1;\n"
                   "    int column1 = column_size1;\n"
                   "\n"
                   "    int row2 = row_size2;\n"
                   "    int column2 = column_size2;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row1 * sizeof(double*));\n"
                   "    for (i = 0; i < row1; i++)\n"
                   "        new_mat[i] = (double*)malloc(column2 * sizeof(double));\n"
                   "\n"
                   "\n"
                   "    for (i = 0; i < row1; i++) {\n"
                   "        for (j = 0; j < column2; j++) {\n"
                   "            new_mat[i][j] = 0;\n"
                   "        }\n"
                   "    }\n"
                   "\n"
                   "    for (i = 0; i < row1; i++) {\n"
                   "        for (j = 0; j < column2; j++) {\n"
                   "            for (k = 0; k < column1; k++) {\n"
                   "                new_mat[i][j] += mat1[i][k] * mat2[k][j];\n"
                   "            }\n"
                   "        }\n"
                   "    }\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **addVectorToMatrix(double *vec1 , double **mat1 , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat1[i][j] + vec1[i];\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **subtractVectorFromMatrix(double *vec1 , double **mat1  , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = mat1[i][j] - vec1[i];\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n"
                   "double **subtractMatrixFromVector(double *vec1 , double **mat1 , int row_size , int column_size)\n"
                   "{\n"
                   "    int i = 0 , j = 0;\n"
                   "\n"
                   "    int row = row_size;\n"
                   "    int column = column_size;\n"
                   "\n"
                   "    double** new_mat = (double**)malloc(row * sizeof(double*));\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        new_mat[i] = (double*)malloc(column * sizeof(double));\n"
                   "\n"
                   "    for (i = 0; i < row; i++)\n"
                   "        for (j = 0; j < column; j++)\n"
                   "            new_mat[i][j] = vec1[i] - mat1[i][j];\n"
                   "\n"
                   "    return new_mat;\n"
                   "}\n"
                   "\n";
    fprintf(out, _other);
}

void createMain(FILE *out) {
    char *code = "int main() {\n";
    fprintf(out, code);
}