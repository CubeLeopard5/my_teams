#include "../../include/server/server.h"

char *read_message_from_client(int fd)
{
    char *buffer = malloc(sizeof(char) * 1024);
    int valread = -1;

    valread = read(fd, buffer, 1024);
    if (valread == -1) {
        perror("Error while reading client message\n");
        return NULL;
    } else if (valread == 0) {
        return NULL;
    } else {
        buffer[valread] = '\0';
        return buffer;
    }
}