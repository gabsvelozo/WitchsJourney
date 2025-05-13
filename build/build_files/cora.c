#include <stdio.h>
#include "raylib.h"
#include "cora.h"
#include "enemy.h"

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


Cora initCora(void) {
    Cora cora;
    cora.health = 100;
    cora.position = (Vector2){100, 800}; 
    cora.speed = (Vector2){5.0f, 0};
    cora.isJumping = false;
    cora.texture = LoadTexture("resources/cora.png");
    cora.facingRight = true;
    cora.isActive = true;
    cora.damage = 20;
    return cora;
}

void updateCora(Cora* cora) {
    const float gravity = 0.5f;
    const float jumpSpeed = -10.0f;
    const float moveSpeed = 5.0f;
    const float groundY = 800; 

    if (IsKeyDown(KEY_RIGHT)) {
        cora->position.x += moveSpeed;
        cora->facingRight = true;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        cora->position.x -= moveSpeed;
        cora->facingRight = false;
    }

    if (!cora->isJumping && IsKeyPressed(KEY_SPACE)) {
        cora->isJumping = true;
        cora->speed.y = jumpSpeed;
    }

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

// ==============================================================


typedef struct {
    Vector2 position;
    Vector2 speed;
    Rectangle hitbox;
    bool isActive;
    bool facingRight;
    int damage;
} Power;

Power initPower(Cora* cora) {
    Power power;
    power.speed = (Vector2){ 10.0f, 0 }; 
    power.isActive = true;
    power.facingRight = cora->facingRight;
    power.damage = cora->damage;

    if (cora->facingRight) {
        power.position = (Vector2){ cora->position.x + cora->texture.width, cora->position.y + cora->texture.height / 2 };
    }
    else {
        power.position = (Vector2){ cora->position.x - 20, cora->position.y + cora->texture.height / 2 };
    }

    power.hitbox = (Rectangle){ power.position.x, power.position.y, 20, 10 }; 

    return power;
}

void updatePower(Power* power) {
    if (!power->isActive) return;

    if (power->facingRight) {
        power->position.x += power->speed.x;
    }
    else {
        power->position.x -= power->speed.x;
    }

    power->hitbox.x = power->position.x;
    power->hitbox.y = power->position.y;

    if (power->position.x < 0 || power->position.x > GetScreenWidth()) {
        power->isActive = false;
    }
}

void drawPower(Power* power) {
    if (power->isActive) {
        DrawRectangleRec(power->hitbox, BLUE);
    }
}

bool checkPowerCollision(Power* power, Enemy* enemy) {
    if (!power->isActive || !enemy->isActive) return false;

    if (CheckCollisionRecs(power->hitbox, enemy->hitbox)) {
        damageEnemy(enemy, power->damage);  // <--- chamada direta
        power->isActive = false;
        return true;
    }

    return false;
}
