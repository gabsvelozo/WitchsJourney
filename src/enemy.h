#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <stdbool.h>

typedef struct type {
    int valor; // valor indo de 1 a 4 e compondo os tipos dos ataques, 1 = Água; 2 = Terra; 3 = Vento; 4 = Fogo;
    struct type *prox;
    struct type* ant;
}type;

typedef enum {
    ENEMY_DOWN,
    ENEMY_UP,
    ENEMY_LEFT,
    ENEMY_RIGHT,
} EnemyDirection;

typedef struct Enemy {
    Vector2 position;
    float speed;
    Texture2D texture;
    Rectangle frameRec;
    int currentFrame;
    int frameCounter;
    int frameSpeed;
    int maxFrames;
    bool active;
    float scale;
    int health;
    Rectangle hitbox;

} Enemy;

void InitEnemy(Enemy* enemy);
void UpdateEnemy(Enemy* enemy, Vector2 targetPosition);
void DrawEnemy(Enemy* enemy);
void UnloadEnemy(Enemy* enemy);

#endif
