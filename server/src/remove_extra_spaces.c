#include "../../include/server/server.h"

char *remove_extra_spaces(char *str)
{
    char *new_string = malloc(sizeof(char) * strlen(str));
    int i = 0;
    int j = 0;

    for (i; str[i] == ' '; i++);
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            new_string[j] = str[i];
            i++;
            j++;
            while (str[i] == ' ') {
                i++;
            }
        } else {
            new_string[j] = str[i];
            i++;
            j++;
        }
    }
    if (j > 0) {
        new_string[--j] = '\0';
    } else {
        new_string[0] = '\0';
    }
    return new_string;
}