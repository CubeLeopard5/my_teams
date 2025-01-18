#include "../../../include/client/client.h"
#include "../../../include/client/frontend.h"

int init_frontend_struct(frontend_t *frontend)
{
    frontend->screen_height = 450;
    frontend->screen_width = 800;
    frontend->screen_title = strdup("my_teams");

    InitWindow(frontend->screen_width, frontend->screen_height, frontend->screen_title);
    SetTargetFPS(FPS);
    return 0;
}
