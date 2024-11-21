#include "state.h"

// Verifica colisão com as bordas
void check_border_collision(Entity *entity, SDL_DisplayMode *display){
    if (entity->x < 0) entity->x = 0;
    if (entity->x > display->w - ELEMENT_SIZE) entity->x = display->w - ELEMENT_SIZE;
    if (entity->y < 0) entity->y = 0;
    if (entity->y > display->h - ELEMENT_SIZE) entity->y = display->h - ELEMENT_SIZE;
}

// Verifica colisão entre entidades
void check_entity_collision(Entity *a, Entity *b) {
    // Verifica se há sobreposição nas coordenadas x e y
    if (a->x < b->x + ELEMENT_SIZE &&
        a->x + ELEMENT_SIZE > b->x &&
        a->y < b->y + ELEMENT_SIZE &&
        a->y + ELEMENT_SIZE > b->y) {
        
        // Calcula as diferenças de posição nos eixos
        float overlap_x = (a->x + ELEMENT_SIZE / 2) - (b->x + ELEMENT_SIZE / 2);
        float overlap_y = (a->y + ELEMENT_SIZE / 2) - (b->y + ELEMENT_SIZE / 2);

        // Ajusta posição no eixo com menor sobreposição
        if (fabs(overlap_x) > fabs(overlap_y)) {
            if (overlap_x > 0) {
                a->x = b->x + ELEMENT_SIZE; // Empurra para a direita
            } else {
                a->x = b->x - ELEMENT_SIZE; // Empurra para a esquerda
            }
        } else {
            if (overlap_y > 0) {
                a->y = b->y + ELEMENT_SIZE; // Empurra para baixo
            } else {
                a->y = b->y - ELEMENT_SIZE; // Empurra para cima
            }
        }
    }
}

// Dispara um projétil
void shoot(Projectile *projectiles, int x, int y, int dx, int dy, int damage) {
    for(int i = 0; i < MAX_PROJECTILES; i++){
        if(!projectiles[i].active){
            projectiles[i].x = x;
            projectiles[i].y = y;

            // Calcula o vetor direção
            /*float dx = projectiles[i].dx - projectiles[i].x;
            float dy = projectiles[i].dy - projectiles[i].y;

            // Calcula a magnitude do vetor
            float magnitude = sqrt(dx * dx + dy * dy);

            // Normaliza o vetor direção
            if(magnitude != 0){
                dx /= magnitude;
                dy /= magnitude;
            }
            else{
                dx = 0;
                dy = 0;
            }
            
            projectiles[i].dx = dx;
            projectiles[i].dy = dy;*/
            projectiles[i].damage = damage;
            projectiles[i].active = 1;

            // define a direção em que o projetil deve ser disparado
            if(projectiles[i].x < projectiles[i].dx) projectiles[i].dx = -1;
            if(projectiles[i].x > projectiles[i].dx) projectiles[i].dx = 1;
            if(projectiles[i].y < projectiles[i].dy) projectiles[i].dy = -1;
            if(projectiles[i].y > projectiles[i].dy) projectiles[i].dy = 1;
  
            while(
                projectiles[i].y > y + ELEMENT_SIZE ||
                projectiles[i].y < y ||
                projectiles[i].x > x + ELEMENT_SIZE ||
                projectiles[i].x < x
            ){
                projectiles[i].x += projectiles[i].dx * projectiles[i].speed;
                projectiles[i].y += projectiles[i].dy * projectiles[i].speed;
            }
            break;
        }
    }
}

// vetifica se uma entidade recebeu o projetil
void damage(Entity *entity, Projectile *projectiles){
    for(int i = 0; i < MAX_PROJECTILES; i++){
        if(!projectiles[i].active) continue;
        if(entity->health > 0 &&
            entity->x >= projectiles[i].x && entity->x <= projectiles[i].x + ELEMENT_SIZE ||
            entity->x + ELEMENT_SIZE >= projectiles[i].x && entity->x + ELEMENT_SIZE <= projectiles[i].x + ELEMENT_SIZE
        ){
            entity->health -= projectiles[i].damage;
            projectiles[i].active = 0;
        }
    }
}

void update_projectiles(SDL_DisplayMode *display, Projectile *projectiles, Dinamic_Etities *entities) {
    for(int i=0; i < MAX_PROJECTILES; i++){
        if(!projectiles[i].active) continue;

        // Atualiza a posição do projétil
        projectiles[i].x += projectiles[i].dx * projectiles[i].speed;
        projectiles[i].y += projectiles[i].dy * projectiles[i].speed;

        // Verifica se o projétil saiu da tela
        if(projectiles[i].x < 0 || projectiles[i].x > display->w ||
            projectiles[i].y < 0 || projectiles[i].y > display->h
        ){
            projectiles[i].active = 0; // Desativa o projétil
        }
    }
}

void update_ally(
    SDL_DisplayMode *display,
    Cursor *cursor,
    Dinamic_Etities *entities,
    Projectile *projectiles,
    int *speed
){
    for(int i=0; i<FRIEND_QTD; i++){
        if(entities->allies[i].health == 0) continue;

        damage(&entities->allies[i], projectiles);
        
        switch (entities->allies[i].state){
            case IDLE:
                // Muda para FOLLOW se o aliado estiver em saúde > 0
                if (entities->allies[i].health > 0) {
                    entities->allies[i].state = FOLLOW;
                }
                break;

            case FOLLOW:
                // Calcula a direção em que o aliado deve se mover para alcançar o jogador
                entities->allies[i].target_x = cursor->x;
                entities->allies[i].target_y = cursor->y;

                // Move o aliado em direção ao jogador
                if (entities->allies[i].x < entities->allies[i].target_x) entities->allies[i].x += *speed;
                if (entities->allies[i].x > entities->allies[i].target_x) entities->allies[i].x -= *speed;
                if (entities->allies[i].y < entities->allies[i].target_y) entities->allies[i].y += *speed;
                if (entities->allies[i].y > entities->allies[i].target_y) entities->allies[i].y -= *speed;

                // Evita que o aliado saia da tela
                check_border_collision(&entities->allies[i], display);

                // Verifica se há colisão entre aliados
                for(int j=FRIEND_QTD-1; j>=0; j--){
                    if (i == j) continue;
                    check_entity_collision(&entities->allies[i], &entities->allies[j]);
                }

                // Verifica se há colisão entre aliados e inimigos
                for(int j=0; j<ENEMY_QTD; j++){
                    if(entities->enemies[j].health <= 0) continue;
                    check_entity_collision(&entities->allies[i], &entities->enemies[j]);
                }

                // Verifica se há inimigos próximos para mudar para o estado de ataque
                for (int j=0; j<ENEMY_QTD; j++) {
                    int distance = sqrt(pow(entities->enemies[j].x - entities->allies[i].x, 2) + pow(entities->enemies[j].y - entities->allies[i].y, 2));
                    if (distance < 100 && entities->enemies[j].health > 0){ // Raio de detecção de 100 
                        entities->allies[i].state = ATTACK;
                        break;
                    }
                }
                break;

            case ATTACK:
                // Atacar o inimigo mais próximo
                for(int j=0; j<ENEMY_QTD; j++){
                    int distance = sqrt(pow(entities->enemies[j].x - entities->allies[i].x, 2) + pow(entities->enemies[j].y - entities->allies[i].y, 2));
                    if(distance < 100 && entities->enemies[j].health > 0){
                        shoot(projectiles, entities->allies[i].x, entities->allies[i].y, entities->enemies[j].x, entities->enemies[j].y, 10); // Dispara projetil
                        //return; // Continua atacando este inimigo
                    }
                }
                // Retorna ao estado FOLLOW se não houver inimigos próximos
                entities->allies[i].state = FOLLOW;
                break;

            case DEFEND:
                // Implementação futura: protege uma posição ou o jogador
                break;

            default:
                break;
        }
    }
}

void update_enemy(
    SDL_DisplayMode *display,
    Projectile *projectiles,
    Dinamic_Etities *entities,
    int *speed
){
    for (int i=0; i<ENEMY_QTD; i++) {
        if (entities->enemies[i].health <= 0) continue; // Ignora inimigos mortos

        damage(&entities->enemies[i], projectiles);

        switch (entities->enemies[i].state) {
            case IDLE:
                // Muda para FOLLOW se o inimigo estiver vivo
                if (entities->enemies[i].health > 0) {
                    entities->enemies[i].state = FOLLOW;
                }
                break;

            case FOLLOW: {
                // Inicializa como se a bandeira fosse o alvo
                int target_x = entities->flag->x;
                int target_y = entities->flag->y;
                int min_distance = sqrt(pow(entities->enemies[i].x - entities->flag->x, 2) + pow(entities->enemies[i].y - entities->flag->y, 2));

                // Verifica aliados para encontrar o alvo mais próximo
                for (int j=0; j<FRIEND_QTD; j++) {
                    if (entities->allies[j].health <= 0) continue; // Ignora aliados mortos
                    int distance = sqrt(pow(entities->enemies[i].x - entities->allies[j].x, 2) + pow(entities->enemies[i].y - entities->allies[j].y, 2));
                    if (distance < min_distance) {
                        min_distance = distance;
                        target_x = entities->allies[j].x;
                        target_y = entities->allies[j].y;
                    }
                }

                // Move o inimigo em direção ao alvo mais próximo
                if (entities->enemies[i].x < target_x) entities->enemies[i].x += *speed/4;
                if (entities->enemies[i].x > target_x) entities->enemies[i].x -= *speed/4;
                if (entities->enemies[i].y < target_y) entities->enemies[i].y += *speed/4;
                if (entities->enemies[i].y > target_y) entities->enemies[i].y -= *speed/4;

                // Evita que o inimigo saia da tela
                check_border_collision(&entities->enemies[i], display);

                // Verifica se houve colisão entre inimigos
                for (int j=0; j<ENEMY_QTD; j++) {
                    if (i == j) continue;
                    check_entity_collision(&entities->enemies[i], &entities->enemies[j]);
                }

                // Verifica se houve colisão entre inimigos e aliados
                for (int j=0; j<FRIEND_QTD; j++) {
                    check_entity_collision(&entities->enemies[i], &entities->allies[j]);
                }

                // Se o inimigo estiver próximo o suficiente, muda para o estado ATTACK
                if (min_distance < 50) { // Raio de ataque
                    entities->enemies[i].state = ATTACK;
                }
                break;
            }

            case ATTACK: {
                // Ataca a bandeira ou o aliado mais próximo
                int min_distance = sqrt(pow(entities->enemies[i].x - entities->flag->x, 2) + pow(entities->enemies[i].y - entities->flag->y, 2));
                Entity *target = entities->flag; // Inicialmente, a bandeira é o alvo

                // Verifica aliados para encontrar o mais próximo
                for (int j = 0; j < FRIEND_QTD; j++) {
                    if (entities->allies[j].health <= 0) continue; // Ignora aliados mortos
                    int distance = sqrt(pow(entities->enemies[i].x - entities->allies[j].x, 2) + pow(entities->enemies[i].y - entities->allies[j].y, 2));
                    if (distance < min_distance) {
                        min_distance = distance;
                        target = &entities->allies[j];
                    }
                }

                // Causa dano ao alvo
                shoot(projectiles, entities->enemies[i].x, entities->enemies[i].y, target->x, target->y, 5);

                // Volta para o estado IDLE
                entities->enemies[i].state = IDLE;
                break;
            }

            default:
                break;
        }
    }
}
