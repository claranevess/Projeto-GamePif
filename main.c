#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>   

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Tamanho da tela
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20

//gcc -o rapidball main.c screen.c keyboard.c timer.c -lm para compilar
// ./rapidball

#define NUM_PLATFORMS 5

// Definição da estrutura para as plataformas
typedef struct {
    int x;
    int y;
    int width;
} Platform;

// Função para inicializar as plataformas
void initPlatforms(Platform platforms[]) {
    int i;
    for (i = 0; i < NUM_PLATFORMS; i++) {
        platforms[i].x = rand() % (SCREEN_WIDTH - 5) + 1;
        platforms[i].y = rand() % (SCREEN_HEIGHT - 1) + 1;
        platforms[i].width = rand() % 5 + 5;
    }
}

// Função para desenhar as plataformas
void drawPlatforms(Platform platforms[]) {
    int i, j;
    for (i = 0; i < NUM_PLATFORMS; i++) {
        for (j = 0; j < platforms[i].width; j++) {
            drawCharacter(platforms[i].x + j, platforms[i].y, '=');
        }
    }
}

int main() {
    int maxY;
    int directionY = 1;
    int ballX = SCREEN_WIDTH / 2;
    int ballY = 1;
    Platform platforms[NUM_PLATFORMS];

    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual

    // Inicializa a tela
    initializeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
    clearScreen();

    maxY = getHeight();

    initPlatforms(platforms);

    // Loop principal do jogo
    while (true) {
        clearScreen();

        // Move a bola
        ballY += directionY;

        // Desenha as plataformas
        drawPlatforms(platforms);

        // Desenha a bola
        drawCharacter(ballX, ballY, 'o');

        // Colisão com as plataformas
        int i;
        for (i = 0; i < NUM_PLATFORMS; i++) {
            if (ballY == platforms[i].y && ballX >= platforms[i].x && ballX < platforms[i].x + platforms[i].width) {
                directionY *= -1;
            }
        }

        // Atualiza a tela
        refreshScreen();
        delay(50); // 50ms de delay
    }

    // Limpa a tela e encerra o jogo
    clearScreen();
    shutdownScreen();

    return 0;
}