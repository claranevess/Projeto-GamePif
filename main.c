#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAXX 80
#define MAXY 24
#define MINX 1
#define MINY 1

// Cores da tela
#define COLOR_PLAYER 6
#define COLOR_PLATFORM 2
#define COLOR_SCORE 14

// Estados do jogo
#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_GAMEOVER 2

typedef struct Platform {
    int x;
    int y;
    int width;
} Platform;

typedef struct Player {
    double x;
    double y;
    double velocityY;
    int onPlatform;
} Player;

Platform platforms[4];
Player player;

int score = 0;
int game_over = 0;
int game_state = STATE_MENU;

void InitializePlayer() {
    player.x = MAXX / 2;
    player.y = MINY + 2;
    player.velocityY = 0;
    player.onPlatform = 0;
}

void InitializePlatforms() {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        platforms[i].x = rand() % (MAXX - 10) + 2;
        platforms[i].y = MAXY - (i + 1) * 5;
        platforms[i].width = 15; // Tamanho da plataforma fixo em 15
    }
}

void MovePlayer(int direction) {
    if (direction == -1 && player.x > MINX + 2)
        player.x -= 2;
    else if (direction == 1 && player.x < MAXX - 3)
        player.x += 2;
}

void ApplyGravity() {
    if (!player.onPlatform) {
        if (player.y < MAXY - 1) {
            player.velocityY += 0.2;
            player.y += player.velocityY;
        } else {
            // Se o jogador cair, ele reaparece no topo da tela
            player.y = MINY + 2;
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
            player.onPlatform = i + 1;
            return;
        }
    }

    // Verifica se o jogador atingiu o topo da tela
    if (player.y <= MINY + 2) {
        if (player.onPlatform != 0) {
            game_over = 1;
            game_state = STATE_GAMEOVER;
        } else {
            player.y = MAXY - 2; // Move o jogador para o fundo da tela
        }
    }
    
    player.onPlatform = 0;
}

void MovePlatforms() {
    for (int i = 0; i < 4; i++) {
        platforms[i].y--;
        if (platforms[i].y < MINY - 5) {
            platforms[i].x = rand() % (MAXX - 10) + 2;
            platforms[i].y = MAXY + rand() % 5;
            platforms[i].width = rand() % 10 + 5;
        }
    }
}

void DrawMenu() {
    screenClear();

    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 6, MAXY / 2 - 2);
    printf("RapidBall Game");
    screenGotoxy(MAXX / 2 - 10, MAXY / 2);
    printf("Pressione ENTER para jogar");
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 2);
    printf("Pressione ESC para sair");

    screenUpdate();
}

void Draw() {
    screenClear();

    screenSetColor(COLOR_PLAYER, DARKGRAY);
    screenGotoxy((int)player.x, (int)player.y);
    printf("  %c", 219);

    screenSetColor(COLOR_PLATFORM, DARKGRAY);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < platforms[i].width; j++) {
            screenGotoxy(platforms[i].x + j, platforms[i].y);
            printf("%c", 219);
        }
    }

    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX - 10, MINY);
    printf("SCORE: %d", score);

    screenUpdate();
}

int main() {
    static int ch = 0;
    int direction = 0; // -1 for left, 1 for right

    screenInit(1);
    keyboardInit();
    timerInit(100);

    while (ch != 27) { // ESC key
        switch (game_state) {
            case STATE_MENU:
                DrawMenu();
                while (ch != 10 && ch != 27) { // ENTER key or ESC key
                    if (keyhit()) {
                        ch = readch();
                    }
                }
                if (ch == 10) { // ENTER key
                    InitializePlayer();
                    InitializePlatforms();
                    game_state = STATE_GAME;
                    ch = 0; // Resetar ch
                }
                break;
            case STATE_GAME:
                if (keyhit()) {
                    ch = readch();
                    if (ch == 97) // 'a' key
                        direction = -1;
                    else if (ch == 115) // 's' key
                        direction = 1;
                }

                if (timerTimeOver() == 1) {
                    MovePlatforms();
                    MovePlayer(direction);
                    ApplyGravity();
                    CheckCollision();
                    Draw();
                }
                break;
            case STATE_GAMEOVER:
                screenClear();
                screenGotoxy(MAXX / 2 - 5, MAXY / 2);
                printf("GAME OVER!");
                screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 2);
                printf("Pressione ENTER para sair");
                screenUpdate();
                while (ch != 10) { // ENTER key
                    if (keyhit()) {
                        ch = readch();
                    }
                }
                game_state = STATE_MENU;
                ch = 0; // Resetar ch
                break;
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
