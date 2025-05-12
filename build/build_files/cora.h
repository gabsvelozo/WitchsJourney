#ifndef CORA_H
#define CORA_H

#include "raylib.h"

typedef struct {
    int health;
    Vector2 position;
    Vector2 speed;
    bool isJumping;
    bool facingRight;
    Texture2D texture;
} Cora;

Cora initCora(void);
void updateCora(Cora* cora);
void drawCora(Cora* cora);

#endif
