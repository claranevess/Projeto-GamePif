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
// Definição da estrutura para as plataformas
typedef struct Platform {
    int x;
    int y;
    int width;
    struct Platform *next;
} Platform;

// Função para inicializar uma plataforma
Platform *initPlatform(int x, int y, int width) {
    Platform *platform = malloc(sizeof(Platform));
    platform->x = x;
    platform->y = y;
    platform->width = width;
    platform->next = NULL;
    return platform;
}

// Função para adicionar uma nova plataforma
Platform *addPlatform(Platform *head, int x, int y, int width) {
    Platform *newPlatform = initPlatform(x, y, width);
    newPlatform->next = head;
    return newPlatform;
}

// Função para desenhar as plataformas
void drawPlatforms(Platform *head) {
    Platform *current = head;
    while (current != NULL) {
        int j;
        for (j = 0; j < current->width; j++) {
            drawCharacter(current->x + j, current->y, '=');
        }
        current = current->next;
    }
}

// Função para liberar a memória das plataformas
void freePlatforms(Platform *head) {
    Platform *current = head;
    while (current != NULL) {
        Platform *temp = current;
        current = current->next;
        free(temp);
    }
}

// Função para gerar uma nova plataforma aleatória
Platform *generateRandomPlatform(int maxY) {
    int x, y, width;
    width = rand() % (PLATFORM_WIDTH_MAX - PLATFORM_WIDTH_MIN + 1) + PLATFORM_WIDTH_MIN;
    y = rand() % (maxY - 1) + 1;
    x = rand() % (SCREEN_WIDTH - width);
    Platform *platform = initPlatform(x, y, width);
    return platform;
}

int main() {
    int maxY;
    int directionY = 1;
    int ballX = SCREEN_WIDTH / 2;
    int ballY = 1;
    int lives = 3;
    int score = 0;
    Platform *platforms = NULL;

    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual

    // Inicializa a tela
    initializeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
    clearScreen();

    maxY = getHeight();

    // Loop principal do jogo
    while (lives > 0) {
        clearScreen();

        // Adiciona uma nova plataforma aleatória
        platforms = addPlatform(platforms, generateRandomPlatform(maxY));

        // Move a bola
        ballY += directionY;

        // Desenha as plataformas
        drawPlatforms(platforms);

        // Desenha a bola
        drawCharacter(ballX, ballY, 'o');

        // Atualiza a tela
        refreshScreen();
        delay(50); // 50ms de delay
    }

    // Limpa a tela e encerra o jogo
    clearScreen();
    shutdownScreen();

    // Libera a memória alocada para as plataformas
    freePlatforms(platforms);

    return 0;
}