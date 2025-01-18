#include "../../include/server/server.h"

char *read_message_from_client(int fd)
{
    char *buffer = (char *)malloc(sizeof(char) * MAX_MSG_LENGTH);
    int valread = -1;

    valread = read(fd, buffer, MAX_MSG_LENGTH); //Reading client input
    if (valread == -1) {
        perror("Error while reading client message\n");
        return NULL;
    } else if (valread == 0) { //User asked for deconnection
        return NULL;
    } else {
        buffer[valread] = '\0';
        return buffer;
    }
}