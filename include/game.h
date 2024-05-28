#ifndef GAME_H
#define GAME_H

// Definições de cores
#define COLOR_PLAYER 6
#define COLOR_PLATFORM 2
#define COLOR_SCORE 14
#define COLOR_SPRINT 5

// Estados do jogo
#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_GAMEOVER 2

extern int score; 
extern int game_state; 
extern int game_over;

void InitializePlayer();
void InitializePlatforms();
void InitializeSprints();
void InitializeLives();
void MovePlayer();
void ApplyGravity();
void CheckCollision();
void CheckSprintCollision();
void MovePlatforms();
void DrawMenu();
void DrawLives();
void Draw();
void DrawSprints();
void DrawSplashScreen();
void DrawPlayerName();
void SaveScores();
void LoadScores();
void DrawTopScores();
void CheckNewScore();
void RemoveUserScore();

#endif