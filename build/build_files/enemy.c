/*#include <stdio.h>
#include "raylib.h"
#include "enemy.h"

typedef struct {
    int health;
    Vector2 position;
    Vector2 speed;
    bool facingRight;
    Texture2D texture;
    Rectangle hitbox;
    bool isActive;
    int damage;
    bool spawnFromRight;
} Enemy;

Enemy initEnemy(Vector2 startPosition, const char* texturePath, bool fromRight) {
    Enemy enemy;
    enemy.health = 50;
    enemy.position = startPosition;
    enemy.spawnFromRight = fromRight;

    // Inimigos da direita se movem para a esquerda, e vice-versa
    enemy.speed = (Vector2){ (fromRight ? -3.0f : 3.0f), 0 }; // Movimento horizontal somente
    enemy.texture = LoadTexture(texturePath);
    enemy.facingRight = !fromRight; // Virado para o lado oposto do spawn
    enemy.isActive = true;
    enemy.damage = 10;

    // Ajusta a hitbox para a posição inicial
    enemy.hitbox = (Rectangle){
        enemy.position.x + 10,
        enemy.position.y + 5,
        enemy.texture.width - 20,
        enemy.texture.height - 5
    };

    return enemy;
}

void updateEnemy(Enemy* enemy) {
    if (!enemy->isActive) return;

    // Movimentação horizontal apenas (sem movimento vertical)
    enemy->position.x += enemy->speed.x;

    // Atualiza hitbox
    enemy->hitbox.x = enemy->position.x + 10;
    enemy->hitbox.y = enemy->position.y + 5;

    // Se o inimigo sair da tela (da esquerda ou da direita), ele se desativa
    if (enemy->position.x < -enemy->texture.width || enemy->position.x > GetScreenWidth() + enemy->texture.width) {
        enemy->isActive = false;  // Desativa inimigo
    }
}

void drawEnemy(Enemy* enemy) {
    if (!enemy->isActive) return;

    // Desenha o inimigo com base na direção que está virado
    Rectangle source = { 0, 0, enemy->texture.width, enemy->texture.height };
    if (!enemy->facingRight) {
        source.width = -source.width; // Flip horizontal para inimigos da esquerda
    }

    DrawTextureRec(enemy->texture, source, enemy->position, WHITE);

    // Debug: desenha hitbox (opcional)
    DrawRectangleLinesEx(enemy->hitbox, 1, RED);
}

void damageEnemy(Enemy* enemy, int damage) {
    if (!enemy->isActive) return;
    enemy->health -= damage;
    if (enemy->health <= 0) {
        enemy->isActive = false; // Morre quando a vida chega a 0
    }
}

void spawnEnemies(Enemy enemies[], int* currentCount, int maxEnemies) {
    for (int i = 0; i < maxEnemies && *currentCount < maxEnemies; i++) {
        bool fromRight = GetRandomValue(0, 1) == 1; // Decide se entra pela direita ou esquerda
        Vector2 spawnPos = fromRight ?
            (Vector2) {
            GetScreenWidth(), GetRandomValue(100, GetScreenHeight() - 100)
        } :  // Entrando pela direita
            (Vector2) {
            -64, GetRandomValue(100, GetScreenHeight() - 100)
        };  // Entrando pela esquerda

            enemies[*currentCount] = initEnemy(spawnPos, "enemy.png", fromRight);
            (*currentCount)++;
    }
}*/

