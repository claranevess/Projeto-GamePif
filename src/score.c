#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"
#include "screen.h"
#include "game.h" // Inclua o cabeçalho onde score está definido

struct Score scores[MAX_SCORES];

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
        strcpy(scores[MAX_SCORES - 1].name, "VOCÊ");
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

void RemoveUserScore() {
    FILE *file = fopen(SCORE_FILE, "r+");
    if (file) {
        struct Score temp_scores[MAX_SCORES];
        int count = 0;
        while (fscanf(file, "%s %d", temp_scores[count].name, &temp_scores[count].score) == 2) {
            count++;
        }
        rewind(file);

        // Remove o nome "VOCÊ" da lista de pontuações
        int new_count = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(temp_scores[i].name, "VOCÊ") != 0) {
                strcpy(temp_scores[new_count].name, temp_scores[i].name);
                temp_scores[new_count].score = temp_scores[i].score;
                new_count++;
            }
        }

        // Reordena as pontuações
        for (int i = 0; i < new_count; i++) {
            for (int j = i + 1; j < new_count; j++) {
                if (temp_scores[j].score > temp_scores[i].score) {
                    struct Score temp = temp_scores[i];
                    temp_scores[i] = temp_scores[j];
                    temp_scores[j] = temp;
                }
            }
        }

        // Escreve as pontuações reordenadas de volta no arquivo
        for (int i = 0; i < new_count && i < MAX_SCORES; i++) {
            fprintf(file, "%s %d\n", temp_scores[i].name, temp_scores[i].score);
        }

        fclose(file);
    }
}