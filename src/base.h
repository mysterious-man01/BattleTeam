#pragma once
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"

// Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ELEMENT_SIZE 40
#define ENEMY_QTD 30
#define FRIEND_QTD 4
#define MAX_PROJECTILES 100

// Enumerators
typedef enum{
    IDLE,
    FOLLOW,
    ATTACK,
    DEFEND
} State;

// Structs
typedef struct{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    TTF_Font *font;
} App;

typedef struct{
    int x, y;
} Cursor;

typedef struct{
    State state;
    int x, y;
    int target_x, target_y;
    int health;
} Entity;

typedef struct{
    Entity *allies;
    Entity *enemies;
    Entity *flag;
} Dinamic_Etities;

typedef struct{
    int x, y;           // Posição atual do projétil
    int dx, dy;         // Direção do movimento
    int speed;
    int active;         // Indica se o projétil está ativo
    int damage;
} Projectile;

typedef struct{
    int points;
    int kills;
    int lost_flags;
    int time;
} Stats;