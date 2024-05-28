#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"
#include "screen.h"
#include "game.h" 

struct Score scores[MAX_SCORES];
extern char playerName[50]; // Declaração externa de playerName

void SaveScores() {
    FILE *file = fopen(SCORE_FILE, "w");
    if (file) {
        for (int i = 0; i < MAX_SCORES; i++) {
            fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
        }
        fclose(file);
    }
}

void LoadScores() {
    FILE *file = fopen(SCORE_FILE, "r");
    if (file) {
        for (int i = 0; i < MAX_SCORES; i++) {
            fscanf(file, "%s %d", scores[i].name, &scores[i].score);
        }
        fclose(file);
    } else {
        // Se o arquivo não existir, inicializa os scores com valores padrão
        for (int i = 0; i < MAX_SCORES; i++) {
            strcpy(scores[i].name, "AAA");
            scores[i].score = 0;
        }
    }
}

void DrawTopScores() {
    screenClear();
    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 6, MINY);
    printf("TOP 10 SCORES");
    for (int i = 0; i < MAX_SCORES; i++) {
        screenGotoxy(MAXX / 2 - 8, MINY + 2 + i);
        printf("%d. %s - %d", i + 1, scores[i].name, scores[i].score);
    }
    screenUpdate();
}

void CheckNewScore() {
    if (score > scores[MAX_SCORES - 1].score) {
        // Adiciona a nova pontuação na lista
        strcpy(scores[MAX_SCORES - 1].name, playerName);
        scores[MAX_SCORES - 1].score = score;

        // Ordena a lista de scores
        for (int i = MAX_SCORES - 1; i > 0; i--) {
            if (scores[i].score > scores[i - 1].score) {
                struct Score temp = scores[i];
                scores[i] = scores[i - 1];
                scores[i - 1] = temp;
            } else {
                break;
            }
        }
        SaveScores();
    }
}
