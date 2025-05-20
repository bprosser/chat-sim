#include "util.h"

#include <string.h>

char *normalize_args(char *args) {
    if (args == NULL)
        return NULL;
    while (*args == ' ')
        args++;

    return (*args == '\0') ? NULL : args;
}
