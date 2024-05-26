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
void MovePlayer();
void ApplyGravity();
void CheckCollision();
void RebootBall(); // reboot

#endif