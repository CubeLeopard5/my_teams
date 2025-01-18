#include "../../include/client/client.h"
#include "../../include/client/frontend.h"

int main(int ac, char **av)
{
    client_t client;
    frontend_t frontend;
    char *ip;
    int port;

    if (ac != 3 || atoi(av[1]) == 0 || atoi(av[2]) == 0) {
        perror("Invalid arguments\n");
        return 84;
    }
    if (init_client_struct(&client, av[1], atoi(av[2])) != 0) {
        return 84;
    }
    if (connect_to_server(&client) != 0) {
        return 84;
    }
    
    init_frontend_struct(&frontend);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        if (loop_client(&client) != 0) {
            return 84;
        }
    }

    CloseWindow();

    return 0;
}