#include <stdio.h>
#include "raylib.h"

typedef struct {
	int health;
	Vector2 position; 
	Vector2 speed; 
	bool facingRight;
	Texture2D texture; 
} Enemy;

Enemy initEnemy(void) {
    Enemy enemy;
    enemy.health = 50;
    enemy.position = (Vector2){ 100, 800 }; // Posição inicial no "chão"
    enemy.speed = (Vector2){ 5.0f, 0 };
    enemy.texture = LoadTexture("resources/enemy.png");
    enemy.facingRight = true;
    return enemy;
}
