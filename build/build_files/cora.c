//#include <stdio.h>
//#include "raylib.h"
//#include "cora.h"
//#include "enemy.h"

/*typedef struct {
    int health;
    Vector2 position;
    float moveSpeed;
    bool facingRight;
    Texture2D texture;
    Rectangle hitbox;
    int damage;
    bool isActive;
} Cora;

Cora initCora(void) {
    Cora cora;
    cora.health = 100;
    cora.position = (Vector2){ 400, 300 }; // centro da tela
    cora.moveSpeed = 3.0f;
    cora.texture = LoadTexture("resources/cora.png");
    cora.facingRight = true;
    cora.isActive = true;
    cora.damage = 20;
    cora.hitbox = (Rectangle){ cora.position.x, cora.position.y, cora.texture.width, cora.texture.height };
    return cora;
}

void updateCora(Cora* cora) {
    if (IsKeyDown(KEY_RIGHT)) {
        cora->position.x += cora->moveSpeed;
        cora->facingRight = true;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        cora->position.x -= cora->moveSpeed;
        cora->facingRight = false;
    }

    if (IsKeyDown(KEY_UP)) {
        cora->position.y -= cora->moveSpeed;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        cora->position.y += cora->moveSpeed;
    }

    // Atualiza hitbox
    cora->hitbox.x = cora->position.x;
    cora->hitbox.y = cora->position.y;
}

void drawCora(Cora* cora) {
    DrawTextureV(cora->texture, cora->position, WHITE);
}

// ==============================================================
// Poder (tiro ou feitiço lançado pela Cora)

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
    power.speed = (Vector2){ 6.0f, 0 };
    power.isActive = true;
    power.facingRight = cora->facingRight;
    power.damage = cora->damage;

    if (cora->facingRight) {
        power.position = (Vector2){ cora->position.x + cora->texture.width, cora->position.y + cora->texture.height / 2 };
        power.speed.x = 6.0f;
    }
    else {
        power.position = (Vector2){ cora->position.x - 20, cora->position.y + cora->texture.height / 2 };
        power.speed.x = -6.0f;
    }

    power.hitbox = (Rectangle){ power.position.x, power.position.y, 20, 10 };

    return power;
}

void updatePower(Power* power) {
    if (!power->isActive) return;

    power->position.x += power->speed.x;
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
        damageEnemy(enemy, power->damage);
        power->isActive = false;
        return true;
    }

    return false;
}*/
