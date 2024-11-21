#pragma once
#include <math.h>
#include "base.h"
#include "state.h"
#include "draw.c"

void draw_elements(
    App *app,
    SDL_DisplayMode *display,
    Dinamic_Etities *entities,
    Projectile *projectiles,
    Cursor *cursor
);