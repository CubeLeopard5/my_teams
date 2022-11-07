#include "../../include/server/server.h"

int nb_word(const char * str)
{
    int nb = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            nb++;
        }
    }
    return nb + 1;
}

char **create_2d_array(int nb)
{
    char **tab = (char **)calloc(nb, sizeof(char *));

    for (int i = 0; i < nb; i++ ) {
        tab[i] = NULL;
    }
    return tab;
}

char **str_to_word_tab(char *str, char *delim)
{
    int nb = nb_word(str);
    char **tab = create_2d_array(nb + 1);
    char *token;
    int i = 0;

    token = strtok(str, delim);
    while(token != NULL) {
        tab[i] = strdup(token);
        i++;
        token = strtok(NULL, delim);
    }
    return tab;
}