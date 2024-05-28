#include <stdlib.h>
#include <time.h>
#include "sprint.h"
#include "screen.h"
#include "player.h" 
#include "game.h" 

struct Sprint sprints[4];
int timerInicial = 150;
int nextScore = 50;

void InitializeSprints() {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        sprints[i].x = rand() % (MAXX - 2) + 1;
        sprints[i].y = rand() % (MAXY - 10) + 5;
        sprints[i].collected = 0;
    }
}

void CheckSprintCollision() {
    for (int i = 0; i < 4; i++) {
        if (!sprints[i].collected && player.x + 2 >= sprints[i].x && player.x <= sprints[i].x + 1 && player.y + 1 >= sprints[i].y && player.y <= sprints[i].y + 1) {
            sprints[i].collected = 1;
            score += 10; // Aumenta a pontuação quando o jogador coleta um sprint
        }
    }
}

void DrawSprints() {
    screenSetColor(COLOR_SPRINT, DARKGRAY);
    for (int i = 0; i < 4; i++) {
        if (!sprints[i].collected) {
            screenGotoxy(sprints[i].x, sprints[i].y);
            printf("🪙");
        }
    }
}

void updateTimerBasedOnScore(){
    if(score >= nextScore){
        timerInicial -= 10;
        nextScore += 50;
        if(timerInicial < 10){
            timerInicial = 10;
        }
    }
}