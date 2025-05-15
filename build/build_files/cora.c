#include "cora.h"
#include "raylib.h"
#include <raymath.h>

Magic normalMagic;
Magic specialMagic;
Texture2D normalTexture;
Texture2D specialTexture;
float specialCooldown = 0.0f;
float specialCooldownMax = 8.0f;

Cora initCora(void) {
    Cora cora = { 0 };
    cora.health = 100;
    cora.position = (Vector2){ 100, 100 };
    cora.speed = (Vector2){ 2.5f, 2.5f };
    cora.direction = DIR_IDLE;

    // Carregando texturas de spritesheet
    cora.textures[DIR_DOWN] = LoadTexture("resources/assets/baixo.png");
    cora.textures[DIR_UP] = LoadTexture("resources/assets/cima.png");
    cora.textures[DIR_LEFT] = LoadTexture("resources/assets/esquerda.png");
    cora.textures[DIR_RIGHT] = LoadTexture("resources/assets/direita.png");
    cora.textures[DIR_IDLE] = LoadTexture("resources/assets/idle.png");
    char path[128];
    normalMagic.maxFrames = 60;
    normalMagic.frameSpeed = 20;
    normalMagic.currentFrame = 0;
    normalMagic.frameCounter = 0;

    specialMagic.maxFrames = 60;
    specialMagic.frameSpeed = 15;
    specialMagic.currentFrame = 0;
    specialMagic.frameCounter = 0;

    for (int i = 1; i <= 60; i++) {
        sprintf(path, "resources/assets/animation01/%d.png", i);
        normalMagic.frames[i] = LoadTexture(path);

        sprintf(path, "resources/assets/animation02/1_%d.png", i);
        specialMagic.frames[i] = LoadTexture(path);
    }
    // Definindo quantidade de frames de cada anima��o
    cora.frames[DIR_DOWN] = 4;
    cora.frames[DIR_UP] = 4;
    cora.frames[DIR_LEFT] = 7;
    cora.frames[DIR_RIGHT] = 7;
    cora.frames[DIR_IDLE] = 4;

    // Inicializa��o do controle de anima��o
    cora.frameSpeed = 8;
    cora.frameCounter = 0;
    cora.currentFrame = 0;

    // Inicializa o frameRec com base na textura atual
    int maxFrames = cora.frames[cora.direction];
    Texture2D current = cora.textures[cora.direction];
    cora.frameRec = (Rectangle){ 0, 0, (float)(current.width / maxFrames), (float)current.height };

    return cora;
}

void updateCora(Cora* cora) {
    Vector2 input = { 0 };

    if (IsKeyDown(KEY_RIGHT)) {
        input.x += 3;
        cora->direction = DIR_RIGHT;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        input.x -= 3;
        cora->direction = DIR_LEFT;
    }
    else if (IsKeyDown(KEY_UP)) {
        input.y -= 3;
        cora->direction = DIR_UP;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        input.y += 3;
        cora->direction = DIR_DOWN;
    }
    else {
        cora->direction = DIR_IDLE;
    }

    // Atualiza posi��o
    cora->position.x += input.x * cora->speed.x;
    cora->position.y += input.y * cora->speed.y;

    // Atualiza anima��o
    cora->frameCounter++;
    if (cora->frameCounter >= (60 / cora->frameSpeed)) {
        cora->frameCounter = 0;
        cora->currentFrame++;

        if (cora->currentFrame >= cora->frames[cora->direction]) {
            cora->currentFrame = 0;
        }
    }

    // Atualiza recorte da anima��o
    Texture2D current = cora->textures[cora->direction];
    int maxFrames = cora->frames[cora->direction];
    cora->frameRec = (Rectangle){
        cora->currentFrame * (float)(current.width / maxFrames),
        0,
        (float)(current.width / maxFrames),
        (float)current.height
    };
}

void drawCora(Cora* cora) {
    DrawTextureRec(
        cora->textures[cora->direction],
        cora->frameRec,
        cora->position,
        WHITE
    );
}

void unloadCora(Cora* cora) {
    for (int i = 0; i < 5; i++) {
        UnloadTexture(cora->textures[i]);
    }
}

void shootNormalMagic(Cora* cora) {
    if (!normalMagic.active) {
        normalMagic.active = true;
        normalMagic.position = (Vector2){
            cora->position.x + cora->frameRec.width / 2,
            cora->position.y + cora->frameRec.height / 2
        };

        Vector2 mouse = GetMousePosition();
        Vector2 dir = Vector2Normalize(Vector2Subtract(mouse, normalMagic.position));
        normalMagic.velocity = Vector2Scale(dir, 5.0f);
    }
}


void shootSpecialMagic(Cora* cora) {
    if (!specialMagic.active && specialCooldown <= 0.0f) {
        specialMagic.active = true;
        specialMagic.position = (Vector2){
            cora->position.x + cora->frameRec.width / 2,
            cora->position.y + cora->frameRec.height / 2
        };

        Vector2 mouse = GetMousePosition();
        Vector2 dir = Vector2Normalize(Vector2Subtract(mouse, specialMagic.position));
        specialMagic.velocity = Vector2Scale(dir, 8.0f);

        specialCooldown = specialCooldownMax;
    }
}


void updateMagics(float deltaTime) {
    if (normalMagic.active) {
        normalMagic.position = Vector2Add(normalMagic.position, normalMagic.velocity);

        normalMagic.frameCounter++;
        if (normalMagic.frameCounter >= (60 / normalMagic.frameSpeed)) {
            normalMagic.frameCounter = 0;
            normalMagic.currentFrame++;
            if (normalMagic.currentFrame >= normalMagic.maxFrames) {
                normalMagic.active = false;
                normalMagic.currentFrame = 0;
            }
        }

        if (normalMagic.position.x < 0 || normalMagic.position.x > GetScreenWidth() ||
            normalMagic.position.y < 0 || normalMagic.position.y > GetScreenHeight()) {
            normalMagic.active = false;
        }
    }

    if (specialMagic.active) {
        specialMagic.position = Vector2Add(specialMagic.position, specialMagic.velocity);

        specialMagic.frameCounter++;
        if (specialMagic.frameCounter >= (60 / specialMagic.frameSpeed)) {
            specialMagic.frameCounter = 0;
            specialMagic.currentFrame++;
            if (specialMagic.currentFrame >= specialMagic.maxFrames) {
                specialMagic.active = false;
                specialMagic.currentFrame = 0;
            }
        }

        if (specialMagic.position.x < 0 || specialMagic.position.x > GetScreenWidth() ||
            specialMagic.position.y < 0 || specialMagic.position.y > GetScreenHeight()) {
            specialMagic.active = false;
        }
    }

    if (specialCooldown > 0.0f) {
        specialCooldown -= deltaTime;
    }
}



void drawMagics(void) {
    if (normalMagic.active) {
        DrawTexture(normalMagic.frames[normalMagic.currentFrame], normalMagic.position.x, normalMagic.position.y, WHITE);
    }

    if (specialMagic.active) {
        DrawTexture(specialMagic.frames[specialMagic.currentFrame], specialMagic.position.x, specialMagic.position.y, WHITE);
    }

    DrawText(TextFormat("Cooldown: %.1f", specialCooldown > 0 ? specialCooldown : 0),
        10, 10, 20, RED);
}

void unloadMagics(void) {
    for (int i = 0; i < 60; i++) {
        UnloadTexture(normalMagic.frames[i]);
        UnloadTexture(specialMagic.frames[i]);
    }
}