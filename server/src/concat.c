#include "../../include/server/server.h"

int get_length_of_all_messages(char **strs, size_t nb_begin, size_t nb_end)
{
    int nb = 0;

    for (size_t i = nb_begin; i < nb_end; i++) {
        nb += strlen(strs[i]);
    }
    return nb;
}

char *concat_all_messages(char **strs, size_t nb_begin, size_t nb_end)
{
    char *message = malloc(sizeof(char) * (get_nb_word(strs) +
    get_length_of_all_messages(strs, nb_begin, nb_end) + 1));
    int nb = 0;

    for (size_t i = nb_begin; i <= nb_end; i++) {
        for (size_t j = 0; strs[i][j] != '\0'; j++) {
            message[nb] = strs[i][j];
            nb++;
        }
        if (i < nb_end) {
            message[nb] = ' ';
            nb++;
        }
    }
    message[nb] = '\0';
    return message;
}

char *concat(const char *str1, const char *str2)
{
    char *rtn = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    int nb = 0;

    for (int i = 0; str1[i] != '\0'; i++, nb++) {
        rtn[nb] = str1[i];
    }
    for (int i = 0; str2[i] != '\0'; i++, nb++) {
        rtn[nb] = str2[i];
    }
    rtn[nb] = '\0';
    return rtn;
}