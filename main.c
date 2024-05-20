#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
#define COLOR_SPRINT 5

// Estados do jogo
#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_GAMEOVER 2
#define MAX_SCORES 10

struct Platform {
    int x;
    int y;
    int width;
};

struct Player {
    double x;
    double y;
    double velocityY;
    int onPlatform;
};

struct Sprint {
    int x;
    int y;
    int collected;
};

struct Life {
    char icon[3]; // Ícone da vida, representado por um coração
    struct Life *next; // Próximo nó na lista
};

struct HighScore {
    char name[50];
    int score;
};

struct Platform platforms[4];
struct Sprint sprints[4];
struct Player player;
struct Life *lives_head = NULL;
struct HighScore high_scores[MAX_SCORES];

int score = 0;
int game_over = 0;
int game_state = STATE_MENU;
int num_high_scores = 0;

void InitializePlayer() {
    player.x = MAXX / 2;
    player.y = MINX; // O jogador começa na parte de baixo da tela
    player.velocityY = 0;
    player.onPlatform = 0;
}

void InitializePlatforms() {
    srand(time(0));
    int gap = MAXX / 4;
    for (int i = 0; i < 4; i++) {
        platforms[i].x = i * gap + 2;
        platforms[i].y = MAXY - (i + 1) * 5;
        platforms[i].width = 15; // Tamanho da plataforma fixo em 15
    }
}

void InitializeSprints() {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        sprints[i].x = rand() % (MAXX - 2) + 1;
        sprints[i].y = rand() % (MAXY - 10) + 5;
        sprints[i].collected = 0;
    }
}

void InitializeLives() {
    for (int i = 0; i < 3; i++) {
        struct Life *new_life = (struct Life*)malloc(sizeof(struct Life));
        strcpy(new_life->icon, "❤️ "); // Ícone do coração
        new_life->next = lives_head;
        lives_head = new_life;
    }
}

void MovePlayer(int direction) {
    if (direction == -1 && player.x > MINX + 2)
        player.x -= 2;
    else if (direction == 1 && player.x < MAXX - 3)
        player.x += 2;
    direction = 0; 
}


void ApplyGravity() {
    if (!player.onPlatform) {
        if (player.y < MAXY - 1) {
            player.velocityY += 0.2;
            if (player.velocityY > 1.0) { // Limite a velocidadeY
                player.velocityY = 1.0;
            }
            player.y += player.velocityY;
        } else {
            player.y = MAXY - 1;
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
            player.onPlatform = 1;
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
                free(temp);
                if (lives_head == NULL) {
                    game_over = 1;
                    game_state = STATE_GAMEOVER;
                }
            }
        } else {
            player.y = MAXY - 2; // Move o jogador para o fundo da tela
            player.velocityY = 0;
        }
    } else if (player.y > MAXY - 1) {
        player.y = MAXY - 1;
        player.velocityY = 0;
    }

    player.onPlatform = 0;
}

void CheckSprintCollision() {
    for (int i = 0; i < 4; i++) {
        if (!sprints[i].collected && player.x + 2 >= sprints[i].x && player.x <= sprints[i].x + 4 && player.y + 1 >= sprints[i].y && player.y <= sprints[i].y + 1) {
            sprints[i].collected = 1;
            score += 10; // Aumenta a pontuação quando o jogador coleta um sprint
        }
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

void DrawMenu() {
    screenClear();

    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 9, MAXY / 2 - 4);
    printf("### RAPIDBALL GAME ###");
    screenGotoxy(MAXX / 2 - 11, MAXY / 2 - 2);
    printf("Pressione ENTER para jogar");
    screenGotoxy(MAXX / 2 - 11, MAXY / 2);
    printf("Pressione ESC para sair");

    screenSetColor(COLOR_PLATFORM, DARKGRAY);
    for (int i = 0; i < MAXX; i++) {
        screenGotoxy(i, MAXY / 2 + 2);
        printf("-");
    }

    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 4);
    printf("Controles:");
    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 5);
    printf("A - Mover para a esquerda");
    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 6);
    printf("S - Mover para a direita");

    screenUpdate();
}


void DrawSprints(); // Protótipo da função DrawSprints()

void DrawLives() {
    struct Life *current_life = lives_head;
    int x = MINX + 2;
    int y = MINY + 2;

    while (current_life != NULL) {
        screenSetColor(COLOR_SCORE, DARKGRAY);
        screenGotoxy(x, y);
        printf("%s", current_life->icon);
        x += 4; // Espaçamento entre os corações
        current_life = current_life->next;
    }
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

    DrawSprints(); // Desenha os sprints na tela
    DrawLives(); // Desenha as vidas na tela

    screenUpdate();
}

void DrawSprints() {
    screenSetColor(COLOR_SPRINT, DARKGRAY);
    for (int i = 0; i < 4; i++) {
        if (!sprints[i].collected) {
            screenGotoxy(sprints[i].x, sprints[i].y);
            printf("%c%c%c%c", 219, 219, 219, 219);
            screenGotoxy(sprints[i].x, sprints[i].y + 1);
            printf("%c%c%c%c", 219, 219, 219, 219);
        }
    }
}

void DrawSplashScreen() {
    screenClear();
    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(10, 5);
    printf("######     ##     ######    ####    #####    ######     ##     ####     ####");
    screenGotoxy(10, 6);
    printf(" ##  ##   ####     ##  ##    ##      ## ##    ##  ##   ####     ##       ##");
    screenGotoxy(10, 7);
    printf(" ##  ##  ##  ##    ##  ##    ##      ##  ##   ##  ##  ##  ##    ##       ##");
    screenGotoxy(10, 8);
    printf(" #####   ##  ##    #####     ##      ##  ##   #####   ##  ##    ##       ##");
    screenGotoxy(10, 9);
    printf(" ## ##   ######    ##        ##      ##  ##   ##  ##  ######    ##   #   ##   #");
    screenGotoxy(10, 10);
    printf(" ##  ##  ##  ##    ##        ##      ## ##    ##  ##  ##  ##    ##  ##   ##  ##");
    screenGotoxy(10, 11);
    printf("#### ##  ##  ##   ####      ####    #####    ######   ##  ##   #######  #######");

    screenUpdate();

    // Inicializa o timer para 3000 milissegundos (3 segundos)
    timerInit(2000);

    // Loop para esperar o tempo passar
    while (!timerTimeOver()) {
        // Não faça nada, apenas espere o timer expirar
    }
}

// Funções de Escrita e Leitura de Arquivos

void WriteHighScoresToFile() {
    FILE *file = fopen("highscores.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < num_high_scores; i++) {
            fprintf(file, "%s %d\n", high_scores[i].name, high_scores[i].score);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

void ReadHighScoresFromFile() {
    FILE *file = fopen("highscores.txt", "r");
    if (file != NULL) {
        num_high_scores = 0;
        while (fscanf(file, "%s %d", high_scores[num_high_scores].name, &high_scores[num_high_scores].score) != EOF) {
            num_high_scores++;
            if (num_high_scores >= MAX_SCORES) {
                break;
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
}

void AddHighScore(char *name, int score) {
    if (num_high_scores < MAX_SCORES) {
        strcpy(high_scores[num_high_scores].name, name);
        high_scores[num_high_scores].score = score;
        num_high_scores++;
    } else {
        // Encontra a posição para inserir a nova pontuação
        int pos = MAX_SCORES - 1;
        while (pos > 0 && score > high_scores[pos - 1].score) {
            strcpy(high_scores[pos].name, high_scores[pos - 1].name);
            high_scores[pos].score = high_scores[pos - 1].score;
            pos--;
        }
        strcpy(high_scores[pos].name, name);
        high_scores[pos].score = score;
    }
}

void DrawHighScores() {
    screenClear();

    screenSetColor(COLOR_SCORE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 9, 3);
    printf("HIGH SCORES");
    for (int i = 0; i < num_high_scores; i++) {
        screenGotoxy(MAXX / 2 - 9, 5 + i);
        printf("%d. %s - %d", i + 1, high_scores[i].name, high_scores[i].score);
    }

    screenGotoxy(MAXX / 2 - 11, MAXY - 1);
    printf("Pressione ENTER para voltar ao menu");

    screenUpdate();

    while (readch() != 10) {} // Espera até que a tecla ENTER seja pressionada
}

int main() {
    static int ch = 0;
    int direction = 0; 

    screenInit(1);
    keyboardInit();

    // Carregar as pontuações máximas do arquivo
    ReadHighScoresFromFile();

    // Desenhar a tela de splash antes de iniciar o jogo
    DrawSplashScreen();

    // Inicializa o timer principal para o loop do jogo
    timerInit(100);

    while (ch != 27) { // ESC key
        switch (game_state) {
            case STATE_MENU:
                DrawMenu();
                while (ch != 10 && ch != 27 && ch != 49) { // ENTER key, ESC key, or '1' key
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
                    game_state = STATE_GAME;
                    ch = 0; // Resetar ch
                } else if (ch == 49) { // '1' key
                    DrawHighScores(); // Mostrar as pontuações máximas
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

                if (timerTimeOver()) {
                    MovePlatforms();
                    MovePlayer(direction);
                    ApplyGravity();
                    CheckCollision();
                    CheckSprintCollision(); // Verifica a colisão com os sprints
                    Draw();
                    // Reinicia o timer após desenhar a tela
                    timerUpdateTimer(100);
                }
                break;
            case STATE_GAMEOVER:
                screenClear();
                screenGotoxy(MAXX / 2 - 5, MAXY / 2);
                printf("GAME OVER!");
                screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 2);
                printf("Insira seu nome: ");
                char player_name[50];
                scanf("%s", player_name); // Captura o nome do jogador
                AddHighScore(player_name, score); // Adiciona a pontuação máxima do jogador
                WriteHighScoresToFile(); // Escreve as pontuações máximas no arquivo
                screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 4);
                printf("Pressione ENTER para sair");
                screenUpdate();
                while (ch != 10) { // ENTER key
                    if (keyhit()) {
                        ch = readch();
                    }
                }
                score = 0; // Reinicia a pontuação ao sair do estado GAMEOVER
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
