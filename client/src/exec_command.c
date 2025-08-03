#include "../../include/client/client.h"

int exec_command(client_t *client, char *command)
{
    void (*builtins_functions[])(client_t *client, char *command)
    = {&quit, NULL};

    if (command == NULL) {
        perror("No command entered\n");
        return 84;
    }

    for (size_t i = 0; i < sizeof(ALLOWED_COMMANDS)/sizeof(ALLOWED_COMMANDS[0]) - 1; i++) {
        if (strcmp(ALLOWED_COMMANDS[i], command) == 0) {
            (*builtins_functions[i])(client, command);
            return 1;
        }
    }
    return 0;
}