#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "life.h"

int main() {
    static int ch = 0;
    int direction = 0;

    screenInit(1);
    keyboardInit();

    // Carrega os scores do arquivo
    LoadScores();

    // Desenhar a tela de splash antes de iniciar o jogo
    DrawSplashScreen();
    DrawPlayerName();

    // Inicializa o timer principal para o loop do jogo
    timerInit(100);

    while (ch != 27) { // ESC key
        switch (game_state) {
            case STATE_MENU:
                DrawMenu();
                while (ch != 10 && ch != 27 && ch != 116) { // ENTER key ou ESC key ou 'T' key
                    if (keyhit()) {
                        ch = readch();
                    }
                }
                if (ch == 10) { // ENTER key
                    InitializePlayer();
                    InitializePlatforms();
                    InitializeSprints(); // Inicializa os sprints
                    InitializeLives(); // Inicializa as vidas
                    score = 0; // Reinicia a pontuação
                    timerInicial = 150;
                    nextScore = 50;
                    game_state = STATE_GAME;
                    difficultyLevel = 1;
                    ch = 0; // Resetar ch
                } else if (ch == 116) { // 'T' key
                    DrawTopScores();
                    while (ch != 10 && ch != 27) { // ENTER key ou ESC key
                        if (keyhit()) {
                            ch = readch();
                        }
                    }
                    ch = 0; // Resetar ch
                }
                break;
            case STATE_GAME:
                if (keyhit()) {
                    ch = readch();
                    if (ch == 97) // 'a' key
                        direction = -1;
                    else if (ch == 100) // 'd' key
                        direction = 1;
                }

                if (timerTimeOver()) {
                    MovePlatforms();
                    MovePlayer(direction);
                    ApplyGravity();
                    CheckCollision();
                    CheckSprintCollision(); // Verifica a colisão com os sprints
                    updateTimerBasedOnScore();
                    Draw();
                    // Reinicia o timer após desenhar a tela
                    timerUpdateTimer(timerInicial);
                }
                break;
            case STATE_GAMEOVER:
                CheckNewScore(); // Verifica se o novo score está entre os melhores
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

    // Libera a memória alocada para as vidas
    struct Life *current_life = lives_head;
    while (current_life != NULL) {
        struct Life *temp = current_life;
        current_life = current_life->next;
        free(temp);
    }

    return 0;
}