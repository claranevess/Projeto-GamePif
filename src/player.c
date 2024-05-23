#include "player.h"
#include "platform.h"
#include "life.h"
#include "screen.h"
#include "game.h"
#include <stdlib.h>

struct Player player;

void InitializePlayer() {
    player.x = MAXX / 2;
    player.y = MINX; // O jogador começa na parte de baixo da tela
    player.velocityY = 0;
    player.onPlatform = 0;
}

void MovePlayer(int direction) {
    if (direction == -1 && player.x > MINX + 2) {
        player.x -= 2;
    } else if (direction == 1 && player.x < MAXX - 3) {
        player.x += 2;
    }
}

void ApplyGravity() {
    if (!player.onPlatform) {
        if (player.y < MAXY - 1) {
            player.velocityY += 0.2;
            if (player.velocityY > 1.0) { // Limite a velocidadeY
                player.velocityY = 1.0;
            }
            player.y += player.velocityY;
        } else {
            player.y = MAXY - 1;
            player.velocityY = 0;
        }
    }
}

void CheckCollision() {
    // Verifica colisão com as plataformas
    for (int i = 0; i < 4; i++) {
        if (player.y + 1 >= platforms[i].y && 
            player.y <= platforms[i].y && 
            player.x + 2 >= platforms[i].x && 
            player.x <= platforms[i].x + platforms[i].width) {
            player.y = platforms[i].y - 1;
            player.velocityY = 0;
            player.onPlatform = 1;
            return;
        }
    }

    // Verifica se o jogador atingiu o topo da tela
    if (player.y <= MINY + 2) {
        if (player.onPlatform != 0) {
            // Remove uma vida
            if (lives_head != NULL) {
                struct Life *temp = lives_head;
                lives_head = lives_head->next;
                free(temp);
                if (lives_head == NULL) {
                    game_over = 1;
                    game_state = STATE_GAMEOVER;
                }
            }
        } else {
            player.y = MAXY - 2; // Move o jogador para o fundo da tela
            player.velocityY = 0;
        }
    } else if (player.y > MAXY - 1) {
        player.y = MAXY - 1;
        player.velocityY = 0;
    }

    player.onPlatform = 0;
}