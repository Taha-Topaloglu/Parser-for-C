

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "infixtopostfix.h"
#include "structs.h"
#include "stringutils.h"

char* convertIntegerToChar(int N)
{
    char *str= (char *) malloc(200 * sizeof(char));
    sprintf(str, "%d", N);

    return str;
    /*
    int m = N;
    int digit = 0;
    while (m) {

        digit++;

        m /= 10;
    }

    char* arr;

    char arr1[digit];

    arr = (char*)malloc(digit);

    int index = 0;
    while (N) {

        arr1[++index] = N % 10 + '0';

        N /= 10;
    }

    int i;
    for (i = 0; i < index; i++) {
        arr[i] = arr1[index - i];
    }

    arr[i] = '\0';

    return (char*)arr;
     */
}

int isNumber(char* arr) {

    if(isFloat(arr) == 1)
    {
        return 1;
    }

    int i;
    int len = strlen(arr);

    for (i = 0; i < len; i++)
    {
        if (!isdigit(arr[i]))
        {
            return 0;
        }
    }

    return 1;
}

double **transposeVector(double *vec , int size)
{
    int i = 0 , j = 0;

    int row = 1;
    int column = size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));


    for (j = 0; j < column; j++) {
        new_mat[0][j] = vec[j];
    }


    return new_mat;
}

double **transposeMatrix(double **mat , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(column * sizeof(double*));
    for (i = 0; i < column; i++)
        new_mat[i] = (double*)malloc(row * sizeof(double));

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            new_mat[j][i] = mat[i][j];
        }
    }

    return new_mat;
}


double *addScalarToVector(double sca , double *vec , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = vec[i] + sca;
    }

    return new_vec;

}

double *subtractScalarFromVector(double sca , double *vec , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = vec[i] - sca;
    }

    return new_vec;
}

double *subtractVectorFromScalar(double sca , double *vec , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = sca - vec[i];
    }

    return new_vec;
}

double *multiplyScalarWithVector(double sca , double *vec , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = vec[i] * sca;
    }

    return new_vec;
}

double **addScalarToMatrix(double sca , double **mat , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat[i][j] + sca;

    return new_mat;

}

double **subtractScalarFromMatrix(double sca , double **mat , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat[i][j] - sca;

    return new_mat;
}

double **subtractMatrixFromScalar(double sca , double **mat , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = sca - mat[i][j];

    return new_mat;
}

double **multiplyScalarWithMatrix(double sca , double **mat , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat[i][j] * sca;

    return new_mat;
}

double *vectorAddition(double *vec1 , double *vec2 , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = vec1[i] + vec2[i];
    }

    return new_vec;
}

double *vectorSubtraction(double *vec1 , double *vec2 , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = vec1[i] - vec2[i];
    }

    return new_vec;
}

double *vectorMultiplication(double *vec1 , double *vec2 , int v_size)
{
    int i = 0;
    int size = v_size;

    double *new_vec = (double*) malloc(size * sizeof(double));

    for(i = 0 ; i < size ; i++)
    {
        new_vec[i] = vec1[i] * vec2[i];
    }

    return new_vec;
}

double **matrixAddition(double **mat1 , double **mat2 , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat1[i][j] + mat2[i][j];

    return new_mat;
}

double **matrixSubtraction(double **mat1 , double **mat2  , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat1[i][j] - mat2[i][j];

    return new_mat;
}

double **matrixMultiplication(double **mat1 , double **mat2 , int row_size1 , int column_size1 , int row_size2 , int column_size2)
{
    int i = 0 , j = 0 , k = 0;

    int row1 = row_size1;
    int column1 = column_size1;

    int row2 = row_size2;
    int column2 = column_size2;

    double** new_mat = (double**)malloc(row1 * sizeof(double*));
    for (i = 0; i < row1; i++)
        new_mat[i] = (double*)malloc(column2 * sizeof(double));


    for (i = 0; i < row1; i++) {
        for (j = 0; j < column2; j++) {
            new_mat[i][j] = 0;
        }
    }

    for (i = 0; i < row1; i++) {
        for (j = 0; j < column2; j++) {
            for (k = 0; k < column1; k++) {
                new_mat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return new_mat;
}

double **addVectorToMatrix(double *vec1 , double **mat1 , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat1[i][j] + vec1[i];

    return new_mat;
}

double **subtractVectorFromMatrix(double *vec1 , double **mat1  , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = mat1[i][j] - vec1[i];

    return new_mat;
}

double **subtractMatrixFromVector(double *vec1 , double **mat1 , int row_size , int column_size)
{
    int i = 0 , j = 0;

    int row = row_size;
    int column = column_size;

    double** new_mat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++)
        new_mat[i] = (double*)malloc(column * sizeof(double));

    for (i = 0; i < row; i++)
        for (j = 0; j < column; j++)
            new_mat[i][j] = vec1[i] - mat1[i][j];

    return new_mat;
}

int choose(int a , int b , int c , int d)
{
    if(a == 0)
    {
        return b;
    }
    else if(a > 0)
    {
        return c;
    }

    return d;
}


int expressionParsing(char* infix_exp , struct node_for_dll** result)
{
    struct node_for_dll* head = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));

    strcpy(head->data , "");

    head->prev = NULL;
    head->next = NULL;


    infixToPostfix(infix_exp , &head);

    struct node_for_dll* node = head;

    if(node->next->next == NULL)
    {
        struct node_for_dll* temp = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));
        initializeNode(&temp);

        node = node->next;

        strcpy(temp->data,node->data);

        if(isNumber(temp->data) || isVariableScalar(temp->data))
        {
            temp->is_scalar = 1;
        }
        else if(isVariableVector(temp->data))
        {
            temp->is_vector = 1;
            temp->size = findVectorById(temp->data)->size;
        }
        else if(isVariableMatrix(temp->data))
        {
            temp->is_matrix = 1;
            temp->row_size = findMatrixById(temp->data)->rowSize;
            temp->column_size = findMatrixById(temp->data)->columnSize;
        }
        else if(strlen(node->data) > 6 && node->data[0] == 'c' && node->data[1] == 'h' && node->data[2] == 'o' &&
                node->data[3] == 'o' && node->data[4] == 's' && node->data[5] == 'e' && node->data[6] == '(' ) {

            char exp1[1024] = "";
            char exp2[1024] = "";
            char exp3[1024] = "";
            char exp4[1024] = "";

            int j = 7;

            while (j < strlen(node->data) && node->data[j] != ',') {
                appendChar(exp1, node->data[j]);

                j++;
            }

            j++;

            while (j < strlen(node->data) && node->data[j] != ',') {
                appendChar(exp2, node->data[j]);

                j++;
            }

            j++;

            while (j < strlen(node->data) && node->data[j] != ',') {
                appendChar(exp3, node->data[j]);

                j++;
            }

            j++;

            while (j < strlen(node->data) - 1) {
                appendChar(exp4, node->data[j]);

                j++;
            }

            struct node_for_dll *node_1 = NULL;
            struct node_for_dll *node_2 = NULL;
            struct node_for_dll *node_3 = NULL;
            struct node_for_dll *node_4 = NULL;

            int is_valid1 = expressionParsing(exp1, &node_1);
            int is_valid2 = expressionParsing(exp2, &node_2);
            int is_valid3 = expressionParsing(exp3, &node_3);
            int is_valid4 = expressionParsing(exp4, &node_4);

            if (is_valid1 && is_valid2 && is_valid3 && is_valid4) {
                char temp_string[1024] = "";


                temp->is_scalar = 1;

                strcat(temp_string, "choose(");
                strcat(temp_string, node_1->data);
                strcat(temp_string, ",");
                strcat(temp_string, node_2->data);
                strcat(temp_string, ",");
                strcat(temp_string, node_3->data);
                strcat(temp_string, ",");
                strcat(temp_string, node_4->data);
                strcat(temp_string, ")");


                strcpy(temp->data, temp_string);

            }
        }
        else
        {
            return 0;
        }

        *result = temp;

        return 1;
    }


    while(node != NULL)
    {
        if(strlen(node->data) > 6 && node->data[0] == 'c' && node->data[1] == 'h' && node->data[2] == 'o' &&
        node->data[3] == 'o' && node->data[4] == 's' && node->data[5] == 'e' && node->data[6] == '(' )
        {
            char exp1[1024] = "";
            char exp2[1024] = "";
            char exp3[1024] = "";
            char exp4[1024] = "";

            int j = 7;

            while(j < strlen(node->data) && node->data[j] != ',')
            {
                appendChar(exp1 ,  node->data[j]);

                j++;
            }

            j++;

            while(j < strlen(node->data) && node->data[j] != ',')
            {
                appendChar(exp2 ,  node->data[j]);

                j++;
            }

            j++;

            while(j < strlen(node->data) && node->data[j] != ',')
            {
                appendChar(exp3 ,  node->data[j]);

                j++;
            }

            j++;

            while(j < strlen(node->data)-1)
            {
                appendChar(exp4 ,  node->data[j]);

                j++;
            }

            struct node_for_dll* node_1 = NULL;
            struct node_for_dll* node_2 = NULL;
            struct node_for_dll* node_3 = NULL;
            struct node_for_dll* node_4 = NULL;

            int is_valid1 = expressionParsing(exp1 , &node_1);
            int is_valid2 = expressionParsing(exp2 , &node_2);
            int is_valid3 = expressionParsing(exp3 , &node_3);
            int is_valid4 = expressionParsing(exp4 , &node_4);

            if(is_valid1 && is_valid2 && is_valid3 && is_valid4)
            {
                char temp_string[1024] = "";

                struct node_for_dll* new_node = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));
                initializeNode(&new_node);

                new_node->is_scalar = 1;

                strcat(temp_string , "choose(");
                strcat(temp_string , node_1->data);
                strcat(temp_string , ",");
                strcat(temp_string , node_2->data);
                strcat(temp_string , ",");
                strcat(temp_string , node_3->data);
                strcat(temp_string , ",");
                strcat(temp_string , node_4->data);
                strcat(temp_string , ")");


                strcpy(new_node->data , temp_string);

                node->prev->next = new_node;
                new_node->prev = node->prev;


                node = node->next;
                new_node->next = node;

                if(node != NULL)
                {
                    node->prev = new_node;
                }

            }
            else
            {
                return 0;
            }

        }

        else if(strlen(node->data) == 2 && node->data[0] == 't' && node->data[1] == 'r')
        {
            struct node_for_dll* prev = node->prev;
            char temp_string[1024] = "";

            struct node_for_dll* new_node = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));
            initializeNode(&new_node);

            if(isNumber(prev->data))
            {
                strcat(temp_string , prev->data);
            }
            else if(isVariableScalar(prev->data))
            {
                strcat(temp_string , prev->data);
            }
            else if(prev->is_scalar == 1)
            {
                strcat(temp_string , prev->data);

                new_node->is_scalar = 1;
            }
            else if(isVariableVector(prev->data) || prev->is_vector == 1)
            {

                new_node->is_matrix = 1;

                int column_size;
                if(prev->is_vector == 1)
                {
                    column_size = prev->size;
                }
                else
                {
                    column_size = findVectorById(prev->data)->size;
                }

                strcat(temp_string , "transposeVector(");
                strcat(temp_string , prev->data);
                strcat(temp_string ,  ",");
                strcat(temp_string , convertIntegerToChar(column_size));
                strcat(temp_string , ")");

                new_node->row_size = 1;
                new_node->column_size = column_size;
            }
            else if(isVariableMatrix(prev->data) || prev->is_matrix == 1)
            {

                new_node->is_matrix = 1;

                int row_size , column_size;
                if(prev->is_matrix == 1)
                {
                    row_size = prev->row_size;
                    column_size = prev->column_size;
                }
                else
                {
                    row_size = findMatrixById(prev->data)->rowSize;
                    column_size = findMatrixById(prev->data)->columnSize;
                }

                strcat(temp_string , "transposeMatrix(");
                strcat(temp_string , prev->data);
                strcat(temp_string ,  ",");
                strcat(temp_string , convertIntegerToChar(row_size));
                strcat(temp_string ,  ",");
                strcat(temp_string , convertIntegerToChar(column_size));
                strcat(temp_string , ")");

                new_node->row_size = column_size;
                new_node->column_size = row_size;
            }

            else
            {
                return 0;
            }

            strcpy(new_node->data , temp_string);

            prev->prev->next = new_node;
            new_node->prev = prev->prev;


            node = node->next;
            new_node->next = node;

            if(node != NULL)
            {
                node->prev = new_node;
            }


        }
        else if(strlen(node->data) == 4 && node->data[0] == 's' && node->data[1] == 'q' &&
                node->data[2] == 'r' && node->data[3] == 't')
        {

            struct node_for_dll* prev = node->prev;

            char temp_string[1024] = "";

            struct node_for_dll* new_node = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));
            initializeNode(&new_node);

            if(isNumber(prev->data) || isVariableScalar(prev->data) || prev->is_scalar == 1)
            {
                strcat(temp_string , "sqrt(");
                strcat(temp_string , prev->data);
                strcat(temp_string , ")");

                new_node->is_scalar = 1;
            }
            else if(isVariableVector(prev->data) || prev->is_vector)
            {
                int size;
                if(prev->is_vector == 1)
                {
                    size = prev->size;
                }
                else
                {
                    size = findVectorById(prev->data)->size;
                }

                if(size == 1)
                {
                    strcat(temp_string , "sqrt(");
                    strcat(temp_string , prev->data);
                    strcat(temp_string , "[0])");

                    new_node->is_scalar = 1;
                }
                else
                {
                    return 0;
                }
            }
            else if(isVariableMatrix(prev->data) || prev->is_matrix)
            {
                int row_size , column_size;
                if(prev->is_matrix == 1)
                {
                    row_size = prev->row_size;
                    column_size = prev->column_size;
                }
                else
                {
                    row_size = findMatrixById(prev->data)->rowSize;
                    column_size = findMatrixById(prev->data)->columnSize;
                }

                if(row_size == 1 && column_size == 1)
                {
                    strcat(temp_string , "sqrt(");
                    strcat(temp_string , prev->data);
                    strcat(temp_string , "[0][0])");

                    new_node->is_scalar = 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }

            strcpy(new_node->data , temp_string);

            prev->prev->next = new_node;
            new_node->prev = prev->prev;


            node = node->next;
            new_node->next = node;

            if(node != NULL)
            {
                node->prev = new_node;
            }

        }

        else if(isOperator(node->data[0]))
        {
            struct node_for_dll* first = node->prev->prev;
            struct node_for_dll* second = node->prev;

            char temp_string[1024] = "";

            struct node_for_dll* new_node = (struct node_for_dll*)malloc(sizeof(struct node_for_dll));
            initializeNode(&new_node);

            if(node->data[0] == '+')
            {
                if((isNumber(first->data) || isVariableScalar(first->data) || first->is_scalar) &&
                (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    strcat(temp_string , "(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , "+");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ")");

                    new_node->is_scalar = 1;
                }
                else if((isNumber(first->data) || isVariableScalar(first->data) || first->is_scalar) &&
                        (isVariableVector(second->data) || second->is_vector))
                {

                    new_node->is_vector = 1;

                    int size;
                    if(second->is_vector == 1)
                    {
                        size = second->size;
                    }
                    else
                    {
                        size = findVectorById(second->data)->size;
                    }

                    strcat(temp_string , "addScalarToVector(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size));
                    strcat(temp_string , ")");

                    new_node->size = size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    new_node->is_vector = 1;

                    int size;
                    if(first->is_vector == 1)
                    {
                        size = first->size;
                    }
                    else
                    {
                        size = findVectorById(first->data)->size;
                    }


                    strcat(temp_string , "addScalarToVector(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size));
                    strcat(temp_string , ")");

                    new_node->size = size;

                }
                else if((isNumber(first->data) || isVariableScalar(first->data) || first-> is_scalar) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(second->is_matrix == 1)
                    {
                        row_size = second->row_size;
                        column_size = second->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(second->data)->rowSize;
                        column_size = findMatrixById(second->data)->columnSize;
                    }


                    strcat(temp_string , "addScalarToMatrix(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(first->is_matrix == 1)
                    {
                        row_size = first->row_size;
                        column_size = first->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(first->data)->rowSize;
                        column_size = findMatrixById(first->data)->columnSize;
                    }


                    strcat(temp_string , "addScalarToMatrix(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                (isVariableVector(second->data) || second->is_vector))
                {
                    int size1;
                    if(first->is_vector == 1)
                    {
                        size1 = first->size;
                    }
                    else
                    {
                        size1 = findVectorById(first->data)->size;
                    }

                    int size2;
                    if(second->is_vector == 1)
                    {
                        size2 = second->size;
                    }
                    else
                    {
                        size2 = findVectorById(second->data)->size;
                    }

                    if(size1 != size2)
                    {
                        return 0;
                    }

                    strcat(temp_string , "vectorAddition(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size1));
                    strcat(temp_string , ")");

                    new_node->is_vector = 1;
                    new_node->size = size1;

                }

                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isVariableVector(second->data) || second->is_vector))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(first->is_matrix == 1)
                    {
                        row_size = first->row_size;
                        column_size = first->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(first->data)->rowSize;
                        column_size = findMatrixById(first->data)->columnSize;
                    }

                    int size2;
                    if(second->is_vector == 1)
                    {
                        size2 = second->size;
                    }
                    else
                    {
                        size2 = findVectorById(second->data)->size;
                    }


                    if(row_size != size2)
                    {
                        return 0;
                    }


                    strcat(temp_string , "addVectorToMatrix(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(second->is_matrix == 1)
                    {
                        row_size = second->row_size;
                        column_size = second->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(second->data)->rowSize;
                        column_size = findMatrixById(second->data)->columnSize;
                    }

                    int size1;
                    if(first->is_vector == 1)
                    {
                        size1 = first->size;
                    }
                    else
                    {
                        size1 = findVectorById(first->data)->size;
                    }

                    if(row_size != size1)
                    {
                        return 0;
                    }

                    strcat(temp_string , "addVectorToMatrix(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {
                    int row_size1 , column_size1;
                    if(first->is_matrix == 1)
                    {
                        row_size1 = first->row_size;
                        column_size1 = first->column_size;
                    }
                    else
                    {
                        row_size1 = findMatrixById(first->data)->rowSize;
                        column_size1 = findMatrixById(first->data)->columnSize;
                    }

                    int row_size2 , column_size2;
                    if(second->is_matrix == 1)
                    {
                        row_size2 = second->row_size;
                        column_size2 = second->column_size;
                    }
                    else
                    {
                        row_size2 = findMatrixById(second->data)->rowSize;
                        column_size2 = findMatrixById(second->data)->columnSize;
                    }

                    if(row_size1 != row_size2 || column_size1 != column_size2)
                    {
                        return 0;
                    }

                    else
                    {
                        strcat(temp_string , "matrixAddition(");
                        strcat(temp_string , first->data);
                        strcat(temp_string , ",");
                        strcat(temp_string , second->data);
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(row_size1));
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(column_size1));
                        strcat(temp_string , ")");

                        new_node->is_matrix = 1;

                        new_node->row_size = row_size1;
                        new_node->column_size = column_size1;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else if(node->data[0] == '-')
            {
                if((isNumber(first->data) || isVariableScalar(first->data) || first->is_scalar) &&
                   (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    strcat(temp_string , "(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , "-");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ")");

                    new_node->is_scalar = 1;
                }
                else if((isNumber(first->data) || isVariableScalar(first->data) || first->is_scalar) &&
                        (isVariableVector(second->data) || second->is_vector))
                {


                    new_node->is_vector = 1;

                    int size;
                    if(second->is_vector == 1)
                    {
                        size = second->size;
                    }
                    else
                    {
                        size = findVectorById(second->data)->size;
                    }

                    strcat(temp_string , "subtractVectorFromScalar(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size));
                    strcat(temp_string , ")");

                    new_node->size = size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    new_node->is_vector = 1;

                    int size;
                    if(first->is_vector == 1)
                    {
                        size = first->size;
                    }
                    else
                    {
                        size = findVectorById(first->data)->size;
                    }


                    strcat(temp_string , "subtractScalarFromVector(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size));
                    strcat(temp_string , ")");

                    new_node->size = size;

                }
                else if((isNumber(first->data) || isVariableScalar(first->data) || first-> is_scalar) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(second->is_matrix == 1)
                    {
                        row_size = second->row_size;
                        column_size = second->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(second->data)->rowSize;
                        column_size = findMatrixById(second->data)->columnSize;
                    }


                    strcat(temp_string , "subtractMatrixFromScalar(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(first->is_matrix == 1)
                    {
                        row_size = first->row_size;
                        column_size = first->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(first->data)->rowSize;
                        column_size = findMatrixById(first->data)->columnSize;
                    }

                    strcat(temp_string , "subtractScalarFromMatrix(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isVariableVector(second->data) || second->is_vector))
                {
                    int size1;
                    if(first->is_vector == 1)
                    {
                        size1 = first->size;
                    }
                    else
                    {
                        size1 = findVectorById(first->data)->size;
                    }

                    int size2;
                    if(second->is_vector == 1)
                    {
                        size2 = second->size;
                    }
                    else
                    {
                        size2 = findVectorById(second->data)->size;
                    }

                    if(size1 != size2)
                    {
                        return 0;
                    }

                    strcat(temp_string , "vectorSubtraction(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size1));
                    strcat(temp_string , ")");

                    new_node->is_vector = 1;
                    new_node->size = size1;

                }

                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isVariableVector(second->data) || second->is_vector))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(first->is_matrix == 1)
                    {
                        row_size = first->row_size;
                        column_size = first->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(first->data)->rowSize;
                        column_size = findMatrixById(first->data)->columnSize;
                    }

                    int size2;
                    if(second->is_vector == 1)
                    {
                        size2 = second->size;
                    }
                    else
                    {
                        size2 = findVectorById(second->data)->size;
                    }


                    if(row_size != size2)
                    {
                        return 0;
                    }

                    strcat(temp_string , "subtractVectorFromMatrix(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");


                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(second->is_matrix == 1)
                    {
                        row_size = second->row_size;
                        column_size = second->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(second->data)->rowSize;
                        column_size = findMatrixById(second->data)->columnSize;
                    }

                    int size1;
                    if(first->is_vector == 1)
                    {
                        size1 = first->size;
                    }
                    else
                    {
                        size1 = findVectorById(first->data)->size;
                    }

                    if(row_size != size1)
                    {
                        return 0;
                    }


                    strcat(temp_string , "subtractMatrixFromVector(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");


                    new_node->row_size = row_size;
                    new_node->column_size = column_size;


                }
                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {
                    int row_size1 , column_size1;
                    if(first->is_matrix == 1)
                    {
                        row_size1 = first->row_size;
                        column_size1 = first->column_size;
                    }
                    else
                    {
                        row_size1 = findMatrixById(first->data)->rowSize;
                        column_size1 = findMatrixById(first->data)->columnSize;
                    }

                    int row_size2 , column_size2;
                    if(second->is_matrix == 1)
                    {
                        row_size2 = second->row_size;
                        column_size2 = second->column_size;
                    }
                    else
                    {
                        row_size2 = findMatrixById(second->data)->rowSize;
                        column_size2 = findMatrixById(second->data)->columnSize;
                    }

                    if(row_size1 != row_size2 || column_size1 != column_size2)
                    {
                        return 0;
                    }

                    else
                    {
                        strcat(temp_string , "matrixSubtraction(");
                        strcat(temp_string , first->data);
                        strcat(temp_string , ",");
                        strcat(temp_string , second->data);
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(row_size1));
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(column_size1));
                        strcat(temp_string , ")");

                        new_node->is_matrix = 1;

                        new_node->row_size = row_size1;
                        new_node->column_size = column_size1;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {

                if((isNumber(first->data) || isVariableScalar(first->data) || first->is_scalar) &&
                   (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    strcat(temp_string , "(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , "*");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ")");

                    new_node->is_scalar = 1;
                }
                else if((isNumber(first->data) || isVariableScalar(first->data) || first->is_scalar) &&
                        (isVariableVector(second->data) || second->is_vector))
                {

                    new_node->is_vector = 1;

                    int size;
                    if(second->is_vector == 1)
                    {
                        size = second->size;
                    }
                    else
                    {
                        size = findVectorById(second->data)->size;
                    }


                    strcat(temp_string , "multiplyScalarWithVector(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size));
                    strcat(temp_string , ")");

                    new_node->size = size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    new_node->is_vector = 1;

                    int size;
                    if(first->is_vector == 1)
                    {
                        size = first->size;
                    }
                    else
                    {
                        size = findVectorById(first->data)->size;
                    }

                    strcat(temp_string , "multiplyScalarWithVector(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size));
                    strcat(temp_string , ")");

                    new_node->size = size;

                }
                else if((isNumber(first->data) || isVariableScalar(first->data) || first-> is_scalar) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(second->is_matrix == 1)
                    {
                        row_size = second->row_size;
                        column_size = second->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(second->data)->rowSize;
                        column_size = findMatrixById(second->data)->columnSize;
                    }


                    strcat(temp_string , "multiplyScalarWithMatrix(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isNumber(second->data) || isVariableScalar(second->data) || second->is_scalar))
                {

                    new_node->is_matrix = 1;

                    int row_size , column_size;
                    if(first->is_matrix == 1)
                    {
                        row_size = first->row_size;
                        column_size = first->column_size;
                    }
                    else
                    {
                        row_size = findMatrixById(first->data)->rowSize;
                        column_size = findMatrixById(first->data)->columnSize;
                    }


                    strcat(temp_string , "multiplyScalarWithMatrix(");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size));
                    strcat(temp_string , ")");

                    new_node->row_size = row_size;
                    new_node->column_size = column_size;

                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isVariableVector(second->data) || second->is_vector))
                {
                    int size1;
                    if(first->is_vector == 1)
                    {
                        size1 = first->size;
                    }
                    else
                    {
                        size1 = findVectorById(first->data)->size;
                    }

                    int size2;
                    if(second->is_vector == 1)
                    {
                        size2 = second->size;
                    }
                    else
                    {
                        size2 = findVectorById(second->data)->size;
                    }

                    if(size1 != size2)
                    {
                        return 0;
                    }

                    strcat(temp_string , "vectorMultiplication(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size1));
                    strcat(temp_string , ")");

                    new_node->is_vector = 1;
                    new_node->size = size1;

                }

                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isVariableVector(second->data) || second->is_vector))
                {
                    int row_size1 , column_size1;
                    if(first->is_matrix == 1)
                    {
                        row_size1 = first->row_size;
                        column_size1 = first->column_size;
                    }
                    else
                    {
                        row_size1 = findMatrixById(first->data)->rowSize;
                        column_size1 = findMatrixById(first->data)->columnSize;
                    }

                    int size2;
                    if(second->is_vector == 1)
                    {
                        size2 = second->size;
                    }
                    else
                    {
                        size2 = findVectorById(second->data)->size;
                    }

                    if(column_size1 != size2)
                    {
                        return 0;
                    }


                    char str[1024] = "transposeMatrix(transposeVector(";
                    strcat(str , second->data);
                    strcat(str , ",");
                    strcat(str , convertIntegerToChar(size2));
                    strcat(str , ")");
                    strcat(str , ",");
                    strcat(str , "1");
                    strcat(str , ",");
                    strcat(str , convertIntegerToChar(size2));
                    strcat(str , ")");

                    strcat(temp_string , "matrixMultiplication(");
                    strcat(temp_string , first->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , str);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size1));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size1));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size2));
                    strcat(temp_string , ",");
                    strcat(temp_string , "1");
                    strcat(temp_string , ")");

                    new_node->is_matrix = 1;

                    new_node->row_size = row_size1;
                    new_node->column_size = 1;



                }
                else if((isVariableVector(first->data) || first->is_vector) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {
                    int row_size2 , column_size2;
                    if(second->is_matrix == 1)
                    {
                        row_size2 = second->row_size;
                        column_size2 = second->column_size;
                    }
                    else
                    {
                        row_size2 = findMatrixById(second->data)->rowSize;
                        column_size2 = findMatrixById(second->data)->columnSize;
                    }

                    int size1;
                    if(first->is_vector == 1)
                    {
                        size1 = first->size;
                    }
                    else
                    {
                        size1 = findVectorById(first->data)->size;
                    }

                    if(row_size2 != 1)
                    {
                        return 0;
                    }

                    char str[1024] = "transposeMatrix(transposeVector(";
                    strcat(str , first->data);
                    strcat(str , ",");
                    strcat(str , convertIntegerToChar(size1));
                    strcat(str , ")");
                    strcat(str , ",");
                    strcat(str , "1");
                    strcat(str , ",");
                    strcat(str , convertIntegerToChar(size1));
                    strcat(str , ")");

                    strcat(temp_string , "matrixMultiplication(");
                    strcat(temp_string , str);
                    strcat(temp_string , ",");
                    strcat(temp_string , second->data);
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(size1));
                    strcat(temp_string , ",");
                    strcat(temp_string , "1");
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(row_size2));
                    strcat(temp_string , ",");
                    strcat(temp_string , convertIntegerToChar(column_size2));
                    strcat(temp_string , ")");

                    new_node->is_matrix = 1;

                    new_node->row_size = size1;
                    new_node->column_size = column_size2;


                }
                else if((isVariableMatrix(first->data) || first->is_matrix) &&
                        (isVariableMatrix(second->data) || second->is_matrix))
                {
                    int row_size1 , column_size1;
                    if(first->is_matrix == 1)
                    {
                        row_size1 = first->row_size;
                        column_size1 = first->column_size;
                    }
                    else
                    {
                        row_size1 = findMatrixById(first->data)->rowSize;
                        column_size1 = findMatrixById(first->data)->columnSize;
                    }

                    int row_size2 , column_size2;
                    if(second->is_matrix == 1)
                    {
                        row_size2 = second->row_size;
                        column_size2 = second->column_size;
                    }
                    else
                    {
                        row_size2 = findMatrixById(second->data)->rowSize;
                        column_size2 = findMatrixById(second->data)->columnSize;
                    }

                    if(column_size1 != row_size2)
                    {
                        return 0;
                    }

                    else
                    {
                        strcat(temp_string , "matrixMultiplication(");
                        strcat(temp_string , first->data);
                        strcat(temp_string , ",");
                        strcat(temp_string , second->data);
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(row_size1));
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(column_size1));
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(row_size2));
                        strcat(temp_string , ",");
                        strcat(temp_string , convertIntegerToChar(column_size2));
                        strcat(temp_string , ")");

                        new_node->is_matrix = 1;

                        new_node->row_size = row_size1;
                        new_node->column_size = column_size2;
                    }
                }
                else
                {
                    return 0;
                }

            }

            strcpy(new_node->data , temp_string);

            first->prev->next = new_node;
            new_node->prev = first->prev;


            node = node->next;
            new_node->next = node;

            if(node != NULL)
            {
                node->prev = new_node;
            }
        }

        else
        {
            node = node->next;
        }

    }

    *result = head->next;

    return 1;

}