

#ifndef MATLANGPROJECT_FORLOOPS_H
#define MATLANGPROJECT_FORLOOPS_H

#include <mbstring.h>

/**
 * Return 1 if line is a single dimensional -no nested- for loop 0 otherwise
 * @param line
 * @return
 */
int isSingleForLoop(char *line);

/**
 * return 1 if line is a double for loop 0 otherwise
 * @param line
 * @return
 */
int isDoubleForLoop(char *line);

/**
 * return 1 if successfully parsed 0 otherwise
 * @param line
 * @return
 */
int parseSingleForLoop(char *line, FILE *file);

/**
 * return 1 if successfully parsed 0 otherwise
 * @param line
 * @return
 */
int parseDoubleForLoop(char *line, FILE *file);
#endif //MATLANGPROJECT_FORLOOPS_H
