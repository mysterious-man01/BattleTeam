#include "event.h"

void aim_event(SDL_Event *event, Cursor *cursor){
    SDL_GetMouseState(&cursor->x, &cursor->y);
    if(event->button.button == SDL_BUTTON_LEFT){
        printf("Mouse position: (%d, %d)\n", cursor->x, cursor->y);
    }
}

void exit_event(App *app, SDL_Event *event){
    if(event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE){
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        SDL_FreeSurface(app->textSurface);
        SDL_DestroyTexture(app->textTexture);
        SDL_Quit();
        exit(0);
    }
}