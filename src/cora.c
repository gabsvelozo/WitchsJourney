#include "cora.h"
#include "enemy.h"
#include "draw.h"
#include <math.h>

Cora initCora(CoraAnimations anims) {
    Cora cora = { 0 };
    cora.isAlive = true;
    cora.health = 100;
    cora.position = (Vector2){ 640, 360 };
    cora.speed = (Vector2){ 2.5f, 2.5f };
    cora.anims = anims;
    cora.animState = STATE_IDLE;
    cora.direction = DIR_DOWN;
    cora.frameSpeed = 8;
    cora.frameCounter = 0;
    cora.currentFrame = 0;

    int totalFrames = anims.frames[cora.animState][cora.direction];
    Texture2D tex = anims.textures[cora.animState][cora.direction];
    cora.frameRec = (Rectangle){
        0,
        0,
        tex.width / totalFrames,
        tex.height
    };

    // Carregando texturas de spritesheet
    /*cora.textures[DIR_DOWN] = LoadTexture("resources/assets/baixo.png");
    cora.textures[DIR_UP] = LoadTexture("resources/assets/cima.png");
    cora.textures[DIR_LEFT] = LoadTexture("resources/assets/esquerda.png");
    cora.textures[DIR_RIGHT] = LoadTexture("resources/assets/direita.png");
    cora.textures[DIR_IDLE] = LoadTexture("resources/assets/idle.png");

    // Definindo quantidade de frames de cada animação
    cora.frames[DIR_DOWN] = 4;
    cora.frames[DIR_UP] = 4;
    cora.frames[DIR_LEFT] = 7;
    cora.frames[DIR_RIGHT] = 7;
    cora.frames[DIR_IDLE] = 4;

    // Inicialização do controle de animação
    cora.frameSpeed = 8;
    cora.frameCounter = 0;
    cora.currentFrame = 0;

    // Inicializa o frameRec com base na textura atual
    int maxFrames = cora.frames[cora.direction];
    Texture2D current = cora.textures[cora.direction];
    cora.frameRec = (Rectangle){ 0, 0, (float)(current.width / maxFrames), (float)current.height };
    */
    // Define hitbox com base no tamanho do primeiro sprite carregado
    float marginX = cora.frameRec.width * 0.2f;
    
    cora.hitbox = (Rectangle){
        cora.position.x + marginX,
        cora.position.y,
        cora.frameRec.width - 2 * marginX,
        cora.frameRec.height
    };

    return cora;
}

void updateCora(Cora* cora) {
    if (!cora->isAlive) return;

    Vector2 input = { 0 };

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        input.x += 3;
        cora->direction = DIR_RIGHT;
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        input.x -= 3;
        cora->direction = DIR_LEFT;
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        input.y -= 3;
        cora->direction = DIR_UP;
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        input.y += 3;
        cora->direction = DIR_DOWN;
    }
    /*else {
        cora->direction = DIR_IDLE;
    }*/

    // Atualiza posição
    /*cora->position.x += input.x * cora->speed.x;
    cora->position.y += input.y * cora->speed.y;

    // Atualiza animação
    cora->frameCounter++;
    if (cora->frameCounter >= (60 / cora->frameSpeed)) {
        cora->frameCounter = 0;
        cora->currentFrame++;

        if (cora->currentFrame >= cora->frames[cora->direction]) {
            cora->currentFrame = 0;
        }
    }

    // Atualiza recorte da animação
    Texture2D current = cora->textures[cora->direction];
    int maxFrames = cora->frames[cora->direction];
    cora->frameRec = (Rectangle){
        cora->currentFrame * (float)(current.width / maxFrames),
        0,
        (float)(current.width / maxFrames),
        (float)current.height
    };*/

    if (input.x != 0 || input.y != 0) {
        float len = sqrtf(input.x * input.x + input.y * input.y);
        input.x /= len;
        input.y /= len;

        cora->position.x += input.x * cora->speed.x;
        cora->position.y += input.y * cora->speed.y;

        cora->animState = STATE_WALK;

        // Determina direção
        if (input.x < 0 && input.y < 0) cora->direction = DIR_UP_LEFT;
        else if (input.x > 0 && input.y < 0) cora->direction = DIR_UP_RIGHT;
        //else if (input.x < 0 && input.y > 0) cora->direction = DIR_DOWN_LEFT;
        //else if (input.x > 0 && input.y > 0) cora->direction = DIR_DOWN_RIGHT;
        else if (input.x < 0) cora->direction = DIR_LEFT;
        else if (input.x > 0) cora->direction = DIR_RIGHT;
        else if (input.y < 0) cora->direction = DIR_UP;
        else if (input.y > 0) cora->direction = DIR_DOWN;
    }
    else {
        cora->animState = STATE_IDLE;
    }

    // Atualiza animação
    cora->frameCounter++;
    if (cora->frameCounter >= (60 / cora->frameSpeed)) {
        cora->frameCounter = 0;
        cora->currentFrame++;

        int maxFrames = cora->anims.frames[cora->animState][cora->direction];
        if (cora->currentFrame >= maxFrames) {
            cora->currentFrame = 0;
        }
    }

    // Atualiza frameRec com base no frame atual
    Texture2D tex = cora->anims.textures[cora->animState][cora->direction];
    int maxFrames = cora->anims.frames[cora->animState][cora->direction];

    cora->frameRec = (Rectangle){
        cora->currentFrame * (tex.width / maxFrames),
        0,
        tex.width / maxFrames,
        tex.height
    };

    // Atualiza hitbox com a nova posição
     cora->hitbox = (Rectangle){
     cora->position.x + 30,
     cora->position.y,
     cora->frameRec.width - 60,
     cora->frameRec.height
    };
}

void drawCora(Cora* cora) {
    if (!cora->isAlive) return;

    Texture2D tex = cora->anims.textures[cora->animState][cora->direction];

    Rectangle dest = {
        cora->position.x,
        cora->position.y,
        cora->frameRec.width * 2.0f,
        cora->frameRec.height * 2.0f
    };

    DrawTexturePro(tex, cora->frameRec, dest, (Vector2) { 0, 0 }, 0.0f, WHITE);

    DrawText(TextFormat("HP: %d", cora->health), cora->position.x, cora->position.y - 20, 20, RED);
}

void UnloadCora(Cora* cora) {
    // Libera as texturas das animações
    UnloadCoraAnimations(&cora->anims);

    // Adicione aqui qualquer outra liberação de recursos necessária
}

void UnloadCoraAnimations(CoraAnimations* anims) {
    for (int state = 0; state < STATE_COUNT; state++) {
        for (int dir = 0; dir < DIR_COUNT; dir++) {
            UnloadTexture(anims->textures[state][dir]);
        }
    }
}

void checkCoraCollision(Cora* cora, Enemy* enemies, int enemyCount) {
    if (!cora->isAlive) return;

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].active) {
            Rectangle enemyHitbox = {
                enemies[i].position.x,
                enemies[i].position.y,
                enemies[i].frameRec.width * enemies[i].scale,
                enemies[i].frameRec.height * enemies[i].scale
            };

            if (CheckCollisionRecs(cora->hitbox, enemyHitbox)) {
                cora->health -= 10;
                enemies[i].active = false; // opcional: "desativa" o inimigo que bateu
                if (cora->health <= 0) {
                    cora->isAlive = false;
                }
            }
        }
    }
}
