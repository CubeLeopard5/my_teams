#include "../../include/server/server.h"

char **create_2d_array(int nb)
{
    char **tab = (char **)calloc(nb, sizeof(char *));

    for (int i = 0; i < nb; i++ ) {
        tab[i] = NULL;
    }
    return tab;
}

int count_tokens(const char *str, const char *delim) {
    char *tmp = strdup(str);
    char *saveptr;
    char *token;
    int count = 0;

    token = strtok_r(tmp, delim, &saveptr);
    while (token != NULL) {
        count++;
        token = strtok_r(NULL, delim, &saveptr);
    }
    free(tmp);
    return count;
}

char **str_to_word_tab(char *str, char *delim) {
    int nb = count_tokens(str, delim);
    char **tab = create_2d_array(nb + 1);
    char *saveptr;
    char *token;
    int i = 0;

    token = strtok_r(str, delim, &saveptr);
    while (token != NULL) {
        tab[i++] = strdup(token);
        token = strtok_r(NULL, delim, &saveptr);
    }
    return tab;
}
