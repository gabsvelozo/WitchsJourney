#ifndef PROJETIL_H
#define PROJETIL_H

#include "raylib.h"
#include <stdbool.h>
#include "cora.h"

typedef struct AttackType {
    int valor; // valor indo de 1 a 4: 1 = Água; 2 = Terra; 3 = Vento; 4 = Fogo;
    struct AttackType* prox;
    struct AttackType* ant;
} AttackType;


typedef struct Projectile {
    Vector2 position;
    Vector2 direction;
    float speed;
    bool active;
    Texture2D texture;
    Rectangle frameRec;
    float scale;
} Projectile;

void InitProjectile(Projectile* p, Texture2D texture);
void ShootProjectile(Projectile* p, Cora* cora);
void UpdateProjectile(Projectile* p);
void DrawProjectile(Projectile* p);

#endif
