#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    double x;
    double y;
    double velocityY;
    int onPlatform;
};

extern struct Player player; // Adicione esta linha

void InitializePlayer();
void MovePlayer(int direction);
void ApplyGravity();
void CheckCollision();

#endif