#include "../../include/server/server.h"

char *remove_extra_spaces(char *str)
{
    char *newString = malloc(sizeof(char) * strlen(str));
    int i = 0;
    int j = 0;

    for (i; str[i] == ' '; i++);
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            newString[j] = str[i];
            i++;
            j++;
            while (str[i] == ' ') {
                i++;
            }
        } else {
            newString[j] = str[i];
            i++;
            j++;
        }
    }
    newString[j - 1] = '\0';
    return newString;
}