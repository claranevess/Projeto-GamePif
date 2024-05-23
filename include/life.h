#ifndef LIFE_H
#define LIFE_H

struct Life {
    char icon[3];
    struct Life *next;
};

extern struct Life *lives_head;

void InitializeLives();
void DrawLives();

#endif