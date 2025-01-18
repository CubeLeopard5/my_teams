#ifndef FRONTEND_H_
#define FRONTEND_H_

#include "raylib.h"

#define FPS 60

typedef struct frontend_s
{
    int screen_width;
    int screen_height;
    char *screen_title;
}frontend_t;

int init_frontend_struct(frontend_t *frontend);

#endif