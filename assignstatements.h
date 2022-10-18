

#ifndef MATLANGPROJECT_ASSIGNSTATEMENTS_H
#define MATLANGPROJECT_ASSIGNSTATEMENTS_H

/**
 *
 * @param line
 * @return 1 if vector assignment 0 otherwise
 */
#include <stdio.h>
int isUsualVectorAssignment(char *line);

/**
 * return 1 if vector assignment with expression
 * @param line
 * @return
 */
int isVectorAssignmentWithExpression(char *line);

int isMatrixAssignmentWithExpression(char *line);

int parseMatrixAssignmentWithExpression(char *line, FILE *out);

/**
 * return 1 if successfully parsed 0 otherwise
 * @param line
 * @return
 */
int parseVectorAssignmentWithExpression(char *line, FILE *file);

/**
 *
 * @param line
 * @return 1 if matrix assignment 0 otherwise.
 */
int isUsualMatrixAssignment(char *line);

/**
 * Parse the matrix assignment
 * @param line
 * @return 1 if successful 0 otherwise
 */
int parseUsualMatrixAssignment(char *line, FILE *file);

/**
 *
 * @param line
 * @return 1 if successful 0 otherwise
 */
int parseUsualVectorAssignment(char *line, FILE *file);

/**
 *
 * @param line
 * @return 1 if scalar assignment 0 otherwise
 */
int isScalarAssignment(char *line);

/**
 * return 1 if successfull 0 otherwise
 * @param line
 * @return
 */
int parseScalarAssignment(char *line, FILE *file);

#endif //MATLANGPROJECT_ASSIGNSTATEMENTS_H
