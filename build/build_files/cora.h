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
    Rectangle hitbox;
    int damage;
    bool isActive;
} Cora;

Cora initCora(void);
void updateCora(Cora* cora);
void drawCora(Cora* cora);

typedef struct {
    Vector2 position;
    Vector2 speed;
    Rectangle hitbox;
    bool isActive;
    bool facingRight;
    int damage;
} Power;

Power initPower(Cora* cora);
void updatePower(Power* power);
void drawPower(Power* power);
bool checkPowerCollision(Power* power, Enemy* enemy);

#endif
