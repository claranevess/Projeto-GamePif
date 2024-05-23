#ifndef SPRINT_H
#define SPRINT_H

struct Sprint {
    int x;
    int y;
    int collected;
};

extern struct Sprint sprints[4];

void InitializeSprints();
void CheckSprintCollision();
void DrawSprints();

#endif