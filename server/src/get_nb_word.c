#include "../../include/server/server.h"

int get_nb_word(char **tab)
{
    int nb = 0;

    for (size_t i = 0; tab[i] != NULL; i++) {
        nb++;
    }
    return nb;
}