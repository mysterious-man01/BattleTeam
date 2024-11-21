#pragma once
#include "base.h"
#include "state.c"

void damage(Entity *entity, Projectile *projectiles);

void update_projectiles(
    SDL_DisplayMode *display,
    Projectile *projectiles,
    Dinamic_Etities *entities
);

void update_ally(
    SDL_DisplayMode *display,
    Cursor *cursor,
    Dinamic_Etities *entities,
    Projectile *projectiles,
    int *speed
);

void update_enemy(
    SDL_DisplayMode *display,
    Projectile *projectiles,
    Dinamic_Etities *entities,
    int *speed
);