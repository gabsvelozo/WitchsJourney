#include "enemy.h"
#include "cora.h"
#include <math.h>

void InitEnemy(Enemy* enemy) {
    enemy->texture = LoadTexture("resources/assets/enemy.png");

    enemy->scale = 2.0f;

    // Tamanho da tela: 1280x720
    int spawnSide = GetRandomValue(0, 3); // 0: esquerda, 1: direita, 2: cima, 3: baixo
    switch (spawnSide) {
    case 0: // Esquerda
        enemy->position = (Vector2){ -enemy->texture.width, GetRandomValue(0, 720 - enemy->texture.height)};
        break;
    case 1: // Direita
        enemy->position = (Vector2){ 1280, GetRandomValue(0, 720 - enemy->texture.height)};
        break;
    case 2: // Cima
        enemy->position = (Vector2){ GetRandomValue(0, 1280 - enemy->texture.width), -enemy->texture.height };
        break;
    case 3: // Baixo
        enemy->position = (Vector2){ GetRandomValue(0, 1280 - enemy->texture.width), 720 };
        break;
    }

    enemy->speed = 1.5f;
    enemy->maxFrames = 7; // ajuste se sua sprite tiver mais ou menos frames
    enemy->frameSpeed = 10;
    enemy->currentFrame = 0;
    enemy->frameCounter = 0;
    enemy->frameRec = (Rectangle){ 0, 0, (float)(enemy->texture.width / enemy->maxFrames), (float)enemy->texture.height };
    enemy->active = true;
}

void UpdateEnemy(Enemy* enemy, Vector2 targetPosition) {
    if (!enemy->active) return;

    // Movimento em direção à Cora
    Vector2 direction = {
        targetPosition.x - enemy->position.x,
        targetPosition.y - enemy->position.y
    };

    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    enemy->position.x += direction.x * enemy->speed;
    enemy->position.y += direction.y * enemy->speed;

    // Animação
    enemy->frameCounter++;
    if (enemy->frameCounter >= (60 / enemy->frameSpeed)) {
        enemy->frameCounter = 0;
        enemy->currentFrame++;

        if (enemy->currentFrame >= enemy->maxFrames) {
            enemy->currentFrame = 0;
        }

        enemy->frameRec.x = enemy->currentFrame * enemy->frameRec.width;
    }

    // att hitbox
    enemy->hitbox = (Rectangle){
    enemy->position.x,
    enemy->position.y,
    enemy->frameRec.width * enemy->scale,
    enemy->frameRec.height * enemy->scale
    };

}

void DrawEnemy(Enemy* enemy) {
    if (!enemy->active) return;

    Rectangle source = enemy->frameRec;

    Rectangle dest = {
        enemy->position.x,
        enemy->position.y,
        source.width * enemy->scale,
        source.height * enemy->scale
    };

    Vector2 origin = { 0, 0 }; // desenha a partir do canto superior esquerdo

    DrawTexturePro(enemy->texture, source, dest, origin, 0.0f, WHITE);
}

void UnloadEnemy(Enemy* enemy) {
    UnloadTexture(enemy->texture);
}
