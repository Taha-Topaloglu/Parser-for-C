

#ifndef MATLANGPROJECT_EXPRESSIONPARSING_H
#define MATLANGPROJECT_EXPRESSIONPARSING_H
#include "infixtopostfix.h"

char* convertIntegerToChar(int N);

int isNumber(char* arr) ;

double **transposeVector(double *vec , int size);

double **transposeMatrix(double **mat , int row_size , int column_size);

double *addScalarToVector(double sca , double *vec , int v_size);

double *subtractScalarFromVector(double sca , double *vec , int v_size);

double *subtractVectorFromScalar(double sca , double *vec , int v_size);

double *multiplyScalarWithVector(double sca , double *vec , int v_size);

double **addScalarToMatrix(double sca , double **mat , int row_size , int column_size);

double **subtractScalarFromMatrix(double sca , double **mat , int row_size , int column_size);

double **subtractMatrixFromScalar(double sca , double **mat , int row_size , int column_size);

double **multiplyScalarWithMatrix(double sca , double **mat , int row_size , int column_size);

double *vectorAddition(double *vec1 , double *vec2 , int v_size);

double *vectorSubtraction(double *vec1 , double *vec2 , int v_size);

double *vectorMultiplication(double *vec1 , double *vec2 , int v_size);

double **matrixAddition(double **mat1 , double **mat2 , int row_size , int column_size);

double **matrixSubtraction(double **mat1 , double **mat2 , int row_size , int column_size);

double **matrixMultiplication(double **mat1 , double **mat2 , int row_size1 , int column_size1 , int row_size2 , int column_size2);

double **addVectorToMatrix(double *vec1 , double **mat1 , int row_size , int column_size);

double **subtractVectorFromMatrix(double *vec1 , double **mat1 , int row_size , int column_size);

double **subtractMatrixFromVector(double *vec1 , double **mat1 , int row_size , int column_size);

int choose(int a , int b , int c , int d);



int expressionParsing(char* infix_exp , struct node_for_dll** result);
/*
 * In case of an error , it returns 0
 * If there is no error , it returns 1 and updates result array to correct expression
 *
*/

#endif //MATLANGPROJECT_EXPRESSIONPARSING_H
