#include "../../include/server/server.h"

char *remove_extra_spaces(char *str)
{
    int x = 0;

    for(int i = 0; str[i] != '\0'; i++)
        if (!isspace(str[i]) || (i > 0 && !isspace(str[i - 1])))
            str[x++] = str[i];
    str[x] = '\0';
    
    return str;
}