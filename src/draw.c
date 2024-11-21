#include "draw.h"

#define RADIUS 100

/*void hud(App *app){
    // Criar uma superfície de texto
    SDL_Color textColor = {255, 255, 255, 255}; // Branco
    SDL_Surface *textSurface = TTF_RenderText_Solid(app->font, "Vida: 100", textColor);
    if (!textSurface) {
        printf("Erro ao criar superfície de texto: %s\n", TTF_GetError());
    }

    // Criar uma textura a partir da superfície
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(app->renderer, textSurface);
    if (!textTexture) {
        printf("Erro ao criar textura de texto: %s\n", SDL_GetError());
    }
    // Definir a posição e o tamanho para desenhar o texto
    SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h}; // Posição (10, 10)

    // Renderizar o texto na tela
    SDL_RenderCopy(app->renderer, textTexture, NULL, &textRect);
}*/

void cursor_sprite(App *app, Cursor *mouse){
    SDL_Rect rect = {mouse->x, mouse->y, 7, 7};
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app->renderer, &rect);
}

void friend_sprite(App *app, Entity *friend){
    SDL_Rect rect = {friend->x, friend->y, ELEMENT_SIZE, ELEMENT_SIZE};
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 255); // azul
    SDL_RenderFillRect(app->renderer, &rect);
}

void flag_sprite(App *app, Entity *flag){
    SDL_Rect rect = { flag->x, flag->y, ELEMENT_SIZE, ELEMENT_SIZE }; // (x, y, largura, altura)
    SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255); // verde
    SDL_RenderFillRect(app->renderer, &rect);
}

void enemy_sprite(App *app, Entity *enemy){
    SDL_Rect rect = { enemy->x, enemy->y, ELEMENT_SIZE, ELEMENT_SIZE }; // (x, y, largura, altura)
    SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // vermelho
    SDL_RenderFillRect(app->renderer, &rect);
}

void projectile_sprite(App *app, Projectile *projectile){
    SDL_Rect rect = {projectile->x, projectile->y, 5, 5};
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255); // amarelo
    SDL_RenderFillRect(app->renderer, &rect);
}

void enemy_render(App *app, Entity *enemy, int *w, int *h){
    for(int i = 0; i < ENEMY_QTD; i++){
        if(enemy[i].health > 0) continue;
        
        int borda = rand() % 4;

        switch (borda){
            case 0: // Superior
                enemy[i].x = rand() % *w;
                if(enemy[i].x > (*w - ELEMENT_SIZE)) enemy[i].x -= ELEMENT_SIZE;
                enemy[i].y = 0;
                break;
            case 1: // Inferior
                enemy[i].x = rand() % *w;
                if(enemy[i].x > (*w - ELEMENT_SIZE)) enemy[i].x -= ELEMENT_SIZE;
                enemy[i].y = *h - ELEMENT_SIZE;
                break;
            case 2: // Esquerda
                enemy[i].x = 0;
                enemy[i].y = rand() % *h;
                if(enemy[i].y > (*h - ELEMENT_SIZE)) enemy[i].y -= ELEMENT_SIZE;
                break;
            case 3: // Direita
                enemy[i].x = *w - ELEMENT_SIZE;
                enemy[i].y = rand() % *h;
                if(enemy[i].y > (*h - ELEMENT_SIZE)) enemy[i].y -= ELEMENT_SIZE;
                break;
        }
        enemy[i].health = 100;
    }

    for(int i = 0; i < ENEMY_QTD; i++){
        if(enemy[i].health <= 0) continue;
        
        enemy_sprite(app, &enemy[i]);
    }
}

void friend_render(App *app, Entity *friend, int *player_x, int *player_y, int *w, int *h){
    for(int i = 0; i < FRIEND_QTD; i++){
        if(friend[i].health > 0) continue;
        
        do{
            // Gera ângulo e distância aleatórios para posicionar o aliado dentro do raio
            double angle = (rand() % 360) * M_PI / 180.0; // Ângulo aleatório em radianos
            int distance = rand() % RADIUS; // Distância aleatória dentro do raio

            // Calcula as coordenadas baseadas na posição do jogador
            friend[i].x = (*player_x + ELEMENT_SIZE) + (int)(cos(angle) * distance);
            friend[i].y = (*player_y + ELEMENT_SIZE) + (int)(sin(angle) * distance);

            // Garante que o aliado não apareça exatamente na posição do jogador
            if (friend[i].x == *player_x && friend[i].y == *player_y) {
                friend[i].x += 10;
                friend[i].y += 10;
            }
        } while(friend[i].x < 0 || friend[i].x > (*w - ELEMENT_SIZE) || friend[i].y < 0 || friend[i].y > (*h - ELEMENT_SIZE));

        friend[i].health = 100;
    }
    
    for(int i = 0; i < FRIEND_QTD; i++){
        if(friend[i].health <= 0) continue;
        
        friend_sprite(app, &friend[i]);
    }
}

void flag_render(App *app, SDL_DisplayMode *display, Entity *flag, Projectile *projectiles){
    if(flag->health > 0){
        flag_sprite(app, flag);
        damage(flag, projectiles);
    }
    else{
        flag->x = rand() % display->w;
        if(flag->x > (display->w - ELEMENT_SIZE)) flag->x -= ELEMENT_SIZE;

        flag->y = rand() % display->h;
        if(flag->y > (display->h - ELEMENT_SIZE)) flag->y -= ELEMENT_SIZE;

        flag->health = 100;

        //flag_sprite(app, flag); // redundante?
    }
}

void projectile_render(App *app, Projectile *projectiles){
    for(int i=0; i<MAX_PROJECTILES; i++){
        if(!projectiles[i].active) continue;
        projectile_sprite(app, &projectiles[i]);
    }
}

void draw_elements(
    App *app,
    SDL_DisplayMode *display,
    Dinamic_Etities *entities,
    Projectile *projectiles,
    Cursor *cursor
){
    // Limpa a tela com uma cor preta
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    //hud(app);

    flag_render(app, display, entities->flag, projectiles);
    friend_render(app, entities->allies, &cursor->x, &cursor->y, &display->w, &display->h);
    enemy_render(app, entities->enemies, &display->w, &display->h);
    cursor_sprite(app, cursor);
    projectile_render(app, projectiles);

    // Apresenta o que foi desenhado
    SDL_RenderPresent(app->renderer);
}