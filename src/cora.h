#ifndef CORA_H
#define CORA_H

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_IDLE,
    DIR_DYING
} Direction;

typedef struct {
    int health;
    Vector2 position;
    Vector2 speed;
    Texture2D textures[6];     // [DOWN, UP, LEFT, RIGHT, IDLE]
    int frames[6];             // número de frames por direção
    int currentFrame;
    int frameCounter;
    int frameSpeed;
    Rectangle frameRec;
    Direction direction;
    Rectangle hitbox; // hitbox
    bool isAlive;
} Cora;

Cora initCora(void);
void updateCora(Cora* cora);
void drawCora(Cora* cora);
void unloadCora(Cora* cora);

#endif
