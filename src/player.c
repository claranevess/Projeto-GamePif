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
    if (direction == -1 && player.x > MINX + 2) { // verifica se a direção é para esquerda 
        player.x -= 2; // move o jogador duas posições por iteração para esquerda até mudar de direção
    } else if (direction == 1 && player.x < MAXX - 3) { // verifica se é para direita 
        player.x += 2; // move o jogador duas posições por iteração para direita até mudar de direção
    }
}

void ApplyGravity() {
    if (!player.onPlatform) { // verfica se o player está sobre uma plataforma ou não
        if (player.y < MAXY - 1) {// verifica se o jogar não atingiu o limite inferior da tela
            player.velocityY += 0.2; // incrementa a velocidade vertical simulando a gravidade
            if (player.velocityY > 1.0) { 
                player.velocityY = 1.0; // limitar a velocidade vertical a um para que o player não caia muito rápido
            }
            player.y += player.velocityY; // atualiza a posição vertical do player
        } else {
            player.y = MAXY - 1;
            player.velocityY = 0; // reseta a velocidade vertical para zero caso o jogador atinja a parte inferior da tela
        }
    }
}

void CheckCollision() {
    // Verifica colisão com as plataformas
    for (int i = 0; i < 4; i++) { // loop para verificar a colisão do jogador com as 4 plataformas
        if (player.y + 1 >= platforms[i].y && 
            player.y <= platforms[i].y && 
            player.x + 2 >= platforms[i].x && 
            player.x <= platforms[i].x + platforms[i].width) { // Verifica se o jogador está em colisão com a plataforma i. Isso é feito comparando as coordenadas do jogador (player.x e player.y) com as coordenadas e largura da plataforma i.
            player.y = platforms[i].y - 1; // se houver colisão o player é reposicionado logo acima da plataforma
            player.velocityY = 0; // reseta a velocidade para zero
            player.onPlatform = 1; // define que o jogador está acima da plataforma
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
                free(temp); // libera um nó da lista de vidas
                if (lives_head == NULL) { // caso a lista esteja como NULL dá gameover
                    game_over = 1; 
                    game_state = STATE_GAMEOVER;
                }
            }
        } else {
            player.y = MAXY - 2; // Move o jogador para o fundo da tela se ele não estava em uma plataforma
            player.velocityY = 0;
        }
    } else if (player.y > MAXY - 1) { // verifica se o jogador ultrapassou o limite inferior da tela
        player.y = MAXY - 1;
        player.velocityY = 0;
    }

    player.onPlatform = 0; // reseta o estado do jogador para não estar em uma plataforma
}