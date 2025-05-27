
#include "util.h"

#include <string.h>

// This function normalizes input arguments by trimming leading spaces.
// It accepts a pointer to a char string and returns NULL if the input is NULL
// or if it's only whitespace. Otherwise, it returns a pointer to the first
// non-space character.
char *normalize_args(char *args) {
    if (args == NULL)
        return NULL;
    while (*args == ' ')
        args++;

    return (*args == '\0') ? NULL : args;
}
