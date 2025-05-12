#include <stdio.h>
#include "raylib.h"

typedef struct {
    int health;
    Vector2 position;
    Vector2 speed;
    bool isJumping;
    bool facingRight;
    Texture2D texture;
} Cora;

Cora initCora(void) {
    Cora cora;
    cora.health = 100;
    cora.position = (Vector2){100, 800}; // Posição inicial no "chão"
    cora.speed = (Vector2){5.0f, 0};
    cora.isJumping = false;
    cora.texture = LoadTexture("resources/cora.png");
    cora.facingRight = true;
    return cora;
}

void updateCora(Cora* cora) {
    const float gravity = 0.5f;
    const float jumpSpeed = -10.0f;
    const float moveSpeed = 5.0f;
    const float groundY = 800; 

    // Movimento lateral
    if (IsKeyDown(KEY_RIGHT)) {
        cora->position.x += moveSpeed;
        cora->facingRight = true;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        cora->position.x -= moveSpeed;
        cora->facingRight = false;
    }

    // Pulo
    if (!cora->isJumping && IsKeyPressed(KEY_SPACE)) {
        cora->isJumping = true;
        cora->speed.y = jumpSpeed;
    }

    // Gravidade
    if (cora->isJumping) {
        cora->position.y += cora->speed.y;
        cora->speed.y += gravity;

        if (cora->position.y >= groundY) {
            cora->position.y = groundY;
            cora->speed.y = 0;
            cora->isJumping = false;
        }
    }
}

void drawCora(Cora* cora) {
    DrawTextureV(cora->texture, cora->position, WHITE);
}