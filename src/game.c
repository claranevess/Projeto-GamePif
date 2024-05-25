#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "player.h"
#include "platform.h"
#include "sprint.h"
#include "life.h"
#include "score.h"

#define MINX 1
#define MINY 1

// Cores da tela
#define COLOR_PLAYER 6
#define COLOR_PLATFORM 2
#define COLOR_SCORE 14
#define COLOR_SPRINT 5

// Estados do jogo
#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_GAMEOVER 2

int score = 0;
int game_over = 0;
int game_state = STATE_MENU;

char playerName[50]; // Variável para armazenar o nome do jogador

void DrawMenu() {
    screenClear();

    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 4);
    printf("### RAPIDBALL GAME ###");
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 6);
    printf("Bem-vindo, %s!", playerName); // Exibe o nome do jogador
    screenGotoxy(MAXX / 2 - 14, MAXY / 2 - 2);
    printf("Pressione ENTER para jogar");
    screenGotoxy(MAXX / 2 - 14, MAXY / 2);
    printf("Pressione T para ver o Top Scores");
    screenGotoxy(MAXX / 2 - 14, MAXY / 2 + 2);
    printf("Pressione ESC para sair");

    screenSetColor(COLOR_PLATFORM, DARKGRAY);
    for (int i = 0; i < MAXX; i++) {
        screenGotoxy(i, MAXY / 2 + 4);
        printf("-");
    }

    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 6);
    printf("Controles:");
    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 7);
    printf("A - Mover para a esquerda");
    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 8);
    printf("S - Mover para a direita");

    screenUpdate();
}

void DrawSplashScreen() {
    screenClear();
    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(10, 5);
    printf(" ____   __   ____  __  ____  ____   __   __    __   ");
    screenGotoxy(10, 6);
    printf("(  _ \\ / _\\ (  _ \\(  )(    \\(  _ \\ / _\\ (  )  (  )  ");
    screenGotoxy(10, 7);
    printf(" )   //    \\ ) __/ )(  ) D ( ) _ (/    \\/ (_/\\/ (_/\\");
    screenGotoxy(10, 8);
    printf("(__\\_)\\_/\\_/(__)  (__)(____/(____/\\_/\\_/\\____/\\____/");

    screenUpdate();

    // Inicializa o timer para 2000 milissegundos (2 segundos)
    timerInit(2000);

    // Loop para esperar o tempo passar
    while (!timerTimeOver()) {
        // Não faça nada, apenas espere o timer expirar
    }
}
void DrawPlayerName(){
    screenClear();
    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 6);
    printf("Digite seu nome: ");
    char ch = getchar();
    int i = 0, l = 0;
    while(ch != '\n' && i<50){
        playerName[i] = ch;
        screenSetColor(COLOR_SCORE, DARKGRAY);
        screenGotoxy(MAXX / 2 - 10 + l, MAXY / 2 - 5);
        printf("%c", ch);
        l++;
        ch = getchar();
        i++;
    }
    playerName[i] = '\0';
    screenUpdate();
}

void Draw() {
    screenClear();

    screenSetColor(COLOR_PLAYER, DARKGRAY);
    screenGotoxy((int)player.x, (int)player.y);
    printf("🔴");

    screenSetColor(COLOR_PLATFORM, DARKGRAY);
    for (int i = 0; i < 4; i++) {
        screenGotoxy(platforms[i].x, platforms[i].y);
        for (int j = 0; j < platforms[i].width; j++) {
            printf("█"); // Alternativa com caractere ASCII
        }
    }

    DrawSprints(); // Chama a função para desenhar os sprints
    DrawLives(); // Chama a função para desenhar as vidas

    // Exibe o nome do jogador durante o jogo
    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX - 20, MINY + 1);
    printf("Jogador: %s", playerName);

    // Desenhar a pontuação
    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX - 20, MINY + 2);
    printf("Pontuação: %d", score);

    screenUpdate();
}