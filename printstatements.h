

#ifndef MATLANGPROJECT_PRINTSTATEMENTS_H
#define MATLANGPROJECT_PRINTSTATEMENTS_H

/**
 * Return 1 if statement is of form print(id) else 0
 */
#include <stdio.h>
int isUsualPrintIdStatement(char *line);

/**
 * Return 1 if print id with index 0 otherwise
 * @param line
 * @return
 */
int isPrintIdWithIndex(char *line);

int parsePrintIdWithIndex(char *line, FILE* file);

/**
 * Return 1 if line is of form printsep() else 0
 */
int isPrintSepStatement(char *line);

/**
 * parse the statement
 * @param line
 * @return 1 if succesfull 0 otherwise
 */
int parseUsualPrintIdStatement(char *line, FILE *file);

/**
 * parse print sep statement
 * @param line
 * @return 1 if successful 0 otherwise
 */
int parsePrintSepStatement(char *line, FILE *file);

#endif //MATLANGPROJECT_PRINTSTATEMENTS_H
