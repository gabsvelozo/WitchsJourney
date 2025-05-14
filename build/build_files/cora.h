#ifndef CORA_H
#define CORA_H

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
    int frames[5];             // número de frames por direção
    int currentFrame;
    int frameCounter;
    int frameSpeed;
    Rectangle frameRec;
    Direction direction;
} Cora;

Cora initCora(void);
void updateCora(Cora* cora);
void drawCora(Cora* cora);
void unloadCora(Cora* cora);

#endif
