

#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "stringutils.h"
#include "datastructures.h"

static int EMPTY_STRING = 1;
static int NON_EMPTY_STRING = 0;
static int LINE_LIMIT = 256;

int isEmptyString(const char *str, int size) {
    int state = EMPTY_STRING;
    for (int i = 0; i < size; i++) {
        if (str[i] == '\0')
            break;
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
            state = NON_EMPTY_STRING;
            break;
        }
    }
    return state;
}

int getSizeOfString(const char *string) {
    int size = 0;
    while (1) {
        if (string[size] == '\0') {
            size++;
            break;
        } else {
            size++;
        }
    }
    return size;
}

char *strippedString(char *str, int size) {
    char *_str = malloc(LINE_LIMIT * 1);
    int startingPointerIndex = 0;
    for (int i = 0; i < size; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            startingPointerIndex = i;
            break;
        }
    }
    strcpy(_str, str + startingPointerIndex);
    int sizeOfString = getSizeOfString(_str);
    // get the first character before \0
    for (int i = sizeOfString - 2; i > 0; i--) {
        if (_str[i] == ' ' || _str[i] == '\t') {
            _str[i] = '\0';
        } else {
            break;
        }
    }
    return _str;
}

int isCommentLine(const char *str) {
    if (str[0] == '#')
        return 1;
    else
        return 0;
}

int startsWith(const char *source, char *with, int sizeOfWith) {
    if (getSizeOfString(source) < getSizeOfString(with))
        return 0;
    int starts = 1;
    for (int i = 0; i < sizeOfWith; i++) {
        if (source[i] != with[i]) {
            starts = 0;
            break;
        }
    }
    return starts;
}

int isScalarDefinition(char *string) {
    if (startsWith(string, "scalar ", 7)) {
        return 1;
    } else
        return 0;
}

int isMatrixDefinition(const char *string) {
    if (startsWith(string, "matrix ", 7)) {
        return 1;
    } else
        return 0;
}

int isVectorDefinition(const char *string) {
    if (startsWith(string, "vector ", 7)) {
        return 1;
    } else
        return 0;
}

char *stripSingleTrailingNewLineCharacter(char *string) {
    int size = getSizeOfString(string);
    if (string[size - 2] == '\n') {
        string[size - 2] = '\0';
    }
    return string;
}

int endsWith(char *string, char ch) {
    int size = getSizeOfString(string);
    if (string[size - 2] == ch)
        return 1;
    else
        return 0;
}

char *stripFromEnd(char *string, char ch) {
    int size = getSizeOfString(string);
    string[size - 2] = '\0';
    return string;
}

int containsOnlyNumbers(char *string) {
    int size = getSizeOfString(string);
    for (int i = 0; i < size; i++) {
        if (string[i] == '\0')
            break;
        int asciiCode = (int) string[i];
        if (asciiCode >= 48 && asciiCode <= 57)
            continue;
        else
            return 0;
    }
    return 1;
}

char *getSpacedVersionOf(char *orig) {
    char *spacedLine = malloc(512);
    int spacedIndex = 0;
    int origIndex = 0;
    int origSize = getSizeOfString(orig);

    while (origIndex < origSize) {
        if (orig[origIndex] == '+' || orig[origIndex] == '-' || orig[origIndex] == '*' || orig[origIndex] == '=' ||
            orig[origIndex] == '{' || orig[origIndex] == '}' || orig[origIndex] == ',' || orig[origIndex] == ':' ||
            orig[origIndex] == '[' || orig[origIndex] == ']' || orig[origIndex] == '(' || orig[origIndex] == ')') {
            spacedLine[spacedIndex] = ' ';
            spacedLine[++spacedIndex] = orig[origIndex];
            spacedLine[++spacedIndex] = ' ';
        } else {
            spacedLine[spacedIndex] = orig[origIndex];
        }
        origIndex++;
        spacedIndex++;
    }
    return spacedLine;
}

int isAlphaNumeric(char *str) {
    int size = getSizeOfString(str);
    for (int i = 0; i < size - 1; i++) {
        if (!isalnum(str[i])) {
            printf("VARIABLE NOT ALPHA NUMERIC\n");
            return 0;
        }
    }

    return 1;
}

int isFloat(char* str) {
    char* strCopy = strdup(str);
    char* temp = strtok(strCopy,".");
    struct Node *head = createNode(temp);
    while (temp != NULL) {
        temp = strtok(NULL, ".");
        appendToLinkedList(head, temp);
    }

    if (getLinkedListSize(head) == 1 && containsOnlyNumbers(getNodeData(head,0))) {
        return 1;
    }
    if (getLinkedListSize(head) != 2)
        return 0;
    if (!containsOnlyNumbers(getNodeData(head, 0)))
        return 0;
    if (!containsOnlyNumbers(getNodeData(head,1)))
        return 0;
    return 1;

}

char* deblank(char* input)
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)
    {
        if (input[i]!=' ')
            output[j]=input[i];
        else
            j--;
    }
    output[j]=0;
    return output;
}

int canCastToInt(double num) {
    int casted = (int) num;
    double precision = 0.000000001;
    if (num - casted < precision || casted+1-num < precision) {
        return 1;
    } else
        return 0;
}