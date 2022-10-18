
#ifndef MATLANGPROJECT_STRINGUTILS_H
#define MATLANGPROJECT_STRINGUTILS_H

/**
 * Check if given string is empty
 * @param str string to check
 * @param size size of the string
 * @return -1 if empty 0 otherwise
 */
int isEmptyString(const char *str, int size);

/**
 * Get the size of string
 * @param string
 * @return size of the string including \0 character
 */
int getSizeOfString(const char *string);

/**
 * Strips a non empty string from trailing and preceding white spaces
 * @param str string to be stripped
 * @param size size of the string
 * @return pointer to stripped string
 */
char *strippedString(char *str, int size);


/**
 * Check if a line is a comment line
 * @param str line to check
 * @return 1 if comment line 0 otherwise
 */
int isCommentLine(const char *str);

/**
 * Check if a string starts with a word
 * @param source string to check if starts with a word
 * @param with word to check against
 * @param sizeOfWith size of with
 * @return 1 if source starts with with else 0
 */
int startsWith(const char *source, char *with, int sizeOfWith);

/**
 * Check if the line is a scalar definition
 * @param string line to check
 * @return 1 if scalar definition 0 otherwise
 */
int isScalarDefinition(char *string);

/**
 * Check if a line is a matrix definition
 * @param string line to check for
 * @return 1 if matrix definition 0 otherwise
 */
int isMatrixDefinition(const char *string);

/**
 * Check if a line is vector definition
 * @param string line to check for
 * @return 1 if vector definition 0 otherwise
 */
int isVectorDefinition(const char *string);

/**
 * Strip single trailing new line character
 * @param string string to strip from
 * @return string stripped from newline
 */
char* stripSingleTrailingNewLineCharacter(char* string);
/**
 * Check if given string ends with given character
 * @param string string to check against
 * @param ch character to check against
 * @return 1 if ends with 0 otherwise
 */
int endsWith(char* string, char ch);

/**
 * Strip the given char from the end of the string presuming the string ends with the char
 * @param string string to chec
 * @param ch character to check
 * @return the stripped string
 */
char* stripFromEnd(char* string, char ch);

/**
 * Check if a string only contains number
 * @param string string to check
 * @return 1 if contains only numbers 0 otherwise
 */
int containsOnlyNumbers(char* string);

/**
 * Creates a new char array which has extra spaces before and after
 * any of the operators  = *  + - { } , [ ] ( )
 * @param orig
 * @return the spaced line which is stored in HEAP
 */
char* getSpacedVersionOf(char* orig);

/**
 * Return 1 if string is alpha numeric 0 otherwise
 * @param
 * @return
 */
int isAlphaNumeric(char* str);

/**
 * check if a string is floating point number
 * return 1 IF it is float 0 otherwise
 */
 int isFloat(char* str);

char* deblank(char* input);
/**
 * Return 1 if number can be casted to int with very little loss
 * @param num
 * @return
 */
int canCastToInt(double num);

#endif //MATLANGPROJECT_STRINGUTILS_H
