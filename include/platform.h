#ifndef PLATFORM_H
#define PLATFORM_H

struct Platform {
    int x;
    int y;
    int width;
};

extern struct Platform platforms[4];

void InitializePlatforms();
void MovePlatforms();

#endif