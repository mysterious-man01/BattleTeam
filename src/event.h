#pragma once
#include "base.h"
#include "event.c"

void aim_event(SDL_Event *event, Cursor *cursor);

void exit_event(App *app, SDL_Event *event);