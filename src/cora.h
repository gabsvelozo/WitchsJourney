#ifndef CORA_H
#include <stdio.h>
#define CORA_H
#define MAX_MAGIC_FRAMES 60

#include "raylib.h"

typedef enum {
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_IDLE
} Direction;

typedef struct {
    int health;
    Vector2 position;
    Vector2 speed;
    Texture2D textures[5];     // [DOWN, UP, LEFT, RIGHT, IDLE]
    int frames[5];             // n�mero de frames por dire��o
    int currentFrame;
    int frameCounter;
    int frameSpeed;
    Rectangle frameRec;
    Direction direction;
} Cora;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    bool active;
    Texture2D frames[MAX_MAGIC_FRAMES];
    int currentFrame;
    int maxFrames;
    int frameCounter;
    int frameSpeed;
} Magic;

Cora initCora(void);
void updateCora(Cora* cora);
void drawCora(Cora* cora);
void unloadCora(Cora* cora);

#endif
