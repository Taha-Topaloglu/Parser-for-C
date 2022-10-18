
#ifndef MATLANGPROJECT_INDEXEDASSIGNMENTS_H
#define MATLANGPROJECT_INDEXEDASSIGNMENTS_H


#include <mbstring.h>

/**
 * return 1 if line is of form a[expr] = expr
 * @param line
 * @return
 */
int isIndexedVectorAssignment(char* line);

/**
 * Return 1 if successfully parsed 0 otherwise
 * @param line
 * @return
 */
int parseIndexedVectorAssignment(char *line, FILE *file);

/**
 * return 1 if is matrix assignment 0 otherwise
 * @param line
 * @return
 */
int isIndexedMatrixAssignment(char* line);

/**
 * return 1 if successfully parsed 0 otherwise
 * @param line
 * @return
 */
int parseIndexedMatrixAssignment(char *line, FILE *file);
#endif //MATLANGPROJECT_INDEXEDASSIGNMENTS_H
