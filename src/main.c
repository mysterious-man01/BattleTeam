#include <stdio.h>
#include "base.h"
#include "event.h"
#include "draw.h"
#include "state.h"

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));
    
    App app;
    SDL_DisplayMode display;
    
    // Inicializa a SDL com o subsistema de vídeo
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erro ao inicializar a SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Obtem a resolução da tela
    if(SDL_GetCurrentDisplayMode(0, &display) != 0){
        printf("Erro ao obter a resolução da tela: %s\n", SDL_GetError());
        SDL_Quit();
    }

    // Inicialize SDL_ttf
    if (TTF_Init() == -1){
        printf("Erro ao inicializar SDL_ttf: %s\n", TTF_GetError());
        return -1;
    }

    // Cria a janela
    app.window = SDL_CreateWindow("Renderizador SDL",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    (display.w) ? display.w : SCREEN_WIDTH,
                                    (display.h) ? display.h : SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
    printf("window created!\n");
    if (!app.window) {
        printf("Erro ao criar a janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // desabilita o cursor do sistema operacional
    SDL_ShowCursor(SDL_DISABLE);
    Cursor cursor;

    // Cria o renderizador
    app.renderer = SDL_CreateRenderer(app.window, -1, 0);
    printf("renderer created!\n");
    if (!app.renderer) {
        printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(app.window);
        SDL_Quit();
        return 1;
    }

    // Carregue uma fonte
    app.font = TTF_OpenFont("../fonts/doomed-regular.ttf", 24); // Tamanho 24
    if (!app.font) {
        printf("Erro ao carregar fonte: %s\n", TTF_GetError());
        return -1;
    }

    // Cria a bandeira
    Entity flag = (Entity){
        .x=0,
        .y=0,
        .health=0
    };
    
    // Inicializa os inimigos
    Entity enemies[ENEMY_QTD];
    for(int i=0; i<ENEMY_QTD; i++) enemies[i] = (Entity){.x=0, .y=0, .health=0};
    
    // inicializa os aliados
    Entity friends[FRIEND_QTD];
    for(int i=0; i<FRIEND_QTD; i++) friends[i] = (Entity){.x=0, .y=0, .target_x=cursor.x, .target_y=cursor.y, .health=0};

    // Centraliza todas as entidades
    Dinamic_Etities entities = (Dinamic_Etities){.allies=friends, .enemies=enemies, .flag=&flag};

    // Inicializa os projeteis
    Projectile projectiles[MAX_PROJECTILES];
    for(int i=0; i<MAX_PROJECTILES; i++) projectiles[MAX_PROJECTILES] = (Projectile){.active=0, .speed=10};

    // Variável de controle de movimento
    int velocity = (((display.w) ? display.w : SCREEN_WIDTH) / 1000) * (((display.h) ? display.h : SCREEN_HEIGHT) / 100);

    // Loop principal
    SDL_Event event;
    while(1){
        // Processa eventos
        while(SDL_PollEvent(&event)){
            exit_event(&app, &event);
            aim_event(&event, &cursor);
        }

        // Renderiza os elementos na tela
        draw_elements(&app, &display, &entities, projectiles, &cursor);

        update_projectiles(&display, projectiles, &entities);

        // Atualiza o estado dos aliados
        update_ally(&display, &cursor, &entities, projectiles, &velocity);

        // Atualiza o estado dos inimigos
        update_enemy(&display, projectiles, &entities, &velocity);

        // Controla a taxa de atualização para evitar sobrecarga
        SDL_Delay(16); // aproximadamente 60 FPS
    }
    return 0;
}
