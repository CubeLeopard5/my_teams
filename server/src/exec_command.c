#include "../../include/server/server.h"

int exec_command(server_t *server, size_t client_nbr, char **command)
{
    void (*builtins_functions[])(server_t *server, size_t client_nbr,
    char **command) = {&help, &login, &send_pvt, &logout, &quit, &display_users, &display_user, NULL}; //Function pointers void function() server_t *server, size_t client_nbr, char **command

    if (command == NULL || command[0] == NULL) {
        perror("No command entered\n");
        return 0;
    }

    for (size_t i = 0; ALLOWED_COMMANDS[i] != NULL; i++) {
        if (strcmp(ALLOWED_COMMANDS[i], command[0]) == 0) { //If allowed command found, execute the related function
            (*builtins_functions[i])(server, client_nbr, command);
            return i;
        }
    }
    perror("No valid command found\n");
    return 0;
}