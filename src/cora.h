#ifndef CORA_H
#define CORA_H

#include "raylib.h"
#include <stdbool.h>
#include <enemy.h>

// cora.h

typedef enum {
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP_LEFT,
    DIR_UP_RIGHT,
    DIR_COUNT // total de direções
} Direction;

typedef enum {
    STATE_IDLE,
    STATE_WALK,
    STATE_DEAD,
    STATE_COUNT // total de estados
} AnimationState;


typedef struct {
    Texture2D textures[STATE_COUNT][DIR_COUNT]; // [idle|walk|dead][up|down|left|right|idle]
    int frames[STATE_COUNT][DIR_COUNT];
} CoraAnimations;

typedef struct {
    bool isAlive;
    int health;
    Vector2 position;
    Vector2 speed;
    Direction direction;
    AnimationState animState;

    int currentFrame;
    int frameCounter;
    int frameSpeed;

    Rectangle frameRec;
    Rectangle hitbox;

    CoraAnimations anims;
} Cora;

Cora initCora(CoraAnimations anims);
void updateCora(Cora* cora);
void drawCora(Cora* cora);
void checkCoraCollision(Cora* cora, Enemy* enemies, int enemyCount);


#endif
