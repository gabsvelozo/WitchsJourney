#include <stdio.h>
#include "raylib.h"
#include "enemy.h"

typedef struct {
	int health;
	Vector2 position; 
	Vector2 speed; 
	bool facingRight;
	Texture2D texture; 
    Rectangle hitbox; //area em que o vilão pode ser golpeado
    bool isActive; //se ele está vivo
    int damage; //o dano que ele causa na Cora
    bool spawnFromRight; // define se o inimigo veio da direita
} Enemy;

Enemy initEnemy(Vector2 startPosition, const char* texturePath, bool fromRight) {
    Enemy enemy;
    enemy.health = 50;
    enemy.position = startPosition;
    enemy.spawnFromRight = fromRight;
    
    // Inimigos da direita se movem para a esquerda, e vice-versa
    enemy.speed = (Vector2){fromRight ? -3.0f : 3.0f, 0};
    enemy.texture = LoadTexture(texturePath);
    enemy.facingRight = !fromRight; // Virado para o lado oposto do spawn
    enemy.isActive = true;
    enemy.damage = 10;
    
    enemy.hitbox = (Rectangle){
        enemy.position.x + 10,
        enemy.position.y + 5,
        enemy.texture.width - 20,
        enemy.texture.height - 5
    };
    
    return enemy;
}

void updateEnemies() {
    for (int i = 0; i < enemiesCount; i++) {
        if (!enemies[i].isActive) continue;
        
        // Movimento baseado no spawn
        enemies[i].position.x += enemies[i].speed.x;
        
        // Remove inimigos que saíram da tela
        if ((enemies[i].spawnFromRight && enemies[i].position.x < -100) ||
            (!enemies[i].spawnFromRight && enemies[i].position.x > screenWidth + 100)) {
            enemies[i].isActive = false;
        }
        
        // Atualiza hitbox
        enemies[i].hitbox.x = enemies[i].position.x + 10;
        enemies[i].hitbox.y = enemies[i].position.y + 5;
    }
}

void DrawEnemies() {
    for (int i = 0; i < enemiesCount; i++) {
        if (!enemies[i].isActive) continue;
        
        Rectangle source = {0, 0, enemies[i].texture.width, enemies[i].texture.height};
        if (enemies[i].spawnFromRight) {
            source.width = -source.width; // Flip horizontal para inimigos da direita
        }
        
        DrawTextureRec(enemies[i].texture, source, enemies[i].position, WHITE);
        
        // Debug: desenha hitbox (opcional)
        DrawRectangleLinesEx(enemies[i].hitbox, 1, RED);
    }
}

void damageEnemy(Enemy* enemy, int damage) {
    if (!enemy->isActive) return;
    enemy->health -= damage;
    if (enemy->health <= 0) {
        enemy->isActive = false;
    }
}

void SpawnEnemies(Enemy enemies[], int *currentCount, int maxEnemies, const DifficultyAI *ai) {
    int enemyCount = CalculateEnemyCount(ai);  // Usa a IA!
    
    for (int i = 0; i < enemyCount && *currentCount < maxEnemies; i++) {
        bool fromRight = GetRandomValue(0, 1) == 1;
        Vector2 spawnPos = fromRight ? 
            (Vector2){GetScreenWidth(), GetRandomValue(100, GetScreenHeight()-100)} :
            (Vector2){-64, GetRandomValue(100, GetScreenHeight()-100)};
        
        // Configura atributos baseados na IA
        int health, damage;
        float speed;
        GetEnemyAttributes(ai, &health, &damage, &speed);
        
        enemies[*currentCount] = InitEnemy(spawnPos, "enemy.png", fromRight);
        enemies[*currentCount].health = health;
        enemies[*currentCount].damage = damage;
        enemies[*currentCount].speed.x = speed * (fromRight ? -1 : 1);
        
        (*currentCount)++;
    }
}