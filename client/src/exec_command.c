#include "../../include/client/client.h"

int exec_command(client_t *client, char *command)
{
    void (*builtins_functions[])(client_t *client, char *command)
    = {&quit, NULL};

    if (command == NULL) {
        perror("No command entered\n");
        return 84;
    }

    for (size_t i = 0; ALLOWED_COMMANDS[i] != NULL; i++) {
        if (strcmp(ALLOWED_COMMANDS[i], command) == 0) {
            (*builtins_functions[i])(client, command);
            return i;
        }
    }
    return 0;
}