#include <stdlib.h>
#include <time.h>
#include "platform.h"
#include "screen.h"
#include "sprint.h"

struct Platform platforms[4];

void InitializePlatforms() {
    srand(time(0));  // Inicializa o gerador de números aleatórios
    int gap = MAXX / 4; // Calcula o espaço entre as plataformas
    for (int i = 0; i < 4; i++) { // Loop para inicializar cada uma das 4 plataformas.
        platforms[i].x = i * gap + 2;
        platforms[i].y = MAXY - (i + 1) * 5;
        platforms[i].width = 15; // Tamanho da plataforma fixo em 15
    }
}

void MovePlatforms() {
    for (int i = 0; i < 4; i++) {
        platforms[i].y--;
        if (platforms[i].y < MINY - 1) {
            platforms[i].y = MAXY;
            platforms[i].x = rand() % (MAXX - platforms[i].width) + 1;

            // Reposiciona os sprints aleatoriamente quando a plataforma atinge o topo da tela
            sprints[i].x = rand() % (MAXX - 4) + 1;
            sprints[i].y = rand() % (MAXY - 10) + 5;
            sprints[i].collected = 0;
        }
    }
}