#include "raylib.h"
#include "cora.h"
#include "enemy.h"
#include "tools.h"
#include "projetil.h"
#include "draw.h"

extern const int screenWidth;
extern const int screenHeight;


void map1(void) {
    bool showHitboxes = false;

    InitWindow(screenWidth, screenHeight, "Mapa 1");
    InitAudioDevice(); // se usar sons
    SetTargetFPS(60);

    InitAssets(); // carrega background1 e coraAnims

    //Texture2D background1 = LoadTexture("resources/assets/background1.png");
    Texture2D magicTex = LoadTexture("resources/assets/projetil.png");
    Cora cora = initCora(anims);
    

    // Cria o proj�til e deixa inativo
    Projectile projectileW;
    InitProjectile(&projectileW, magicTex);

    #define MAX_ENEMIES 10

    // Criando e inicializando v�rios inimigos
    Enemy enemies[MAX_ENEMIES];
    for (int i = 0; i < MAX_ENEMIES; i++) {
        InitEnemy(&enemies[i]);
    }


    while (!WindowShouldClose()) {
        updateCora(&cora);

        if (IsKeyPressed(KEY_H)) {
            showHitboxes = !showHitboxes;
        }

        // Atualize inimigos e fa�a a colis�o AQUI, dentro do loop while
        for (int i = 0; i < MAX_ENEMIES; i++) {
            UpdateEnemy(&enemies[i], cora.position);

            // Atualiza a hitbox do inimigo dentro do UpdateEnemy (j� deve estar feito)

            // Colis�o e dano
            if (enemies[i].active && cora.isAlive &&
                CheckCollisionRecs(cora.hitbox, enemies[i].hitbox)) {

                cora.health -= 1;
                if (cora.health <= 0) {
                    cora.health = 0;
                    cora.isAlive = false;
                }
            }
        }        

        if (projectileW.active) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (enemies[i].active &&
                    CheckCollisionCircleRec(projectileW.position, projectileW.frameRec.width * projectileW.scale * 0.5f,
                        enemies[i].hitbox)) {

                    enemies[i].health -= 1;  // dano
                    projectileW.active = false;

                    if (enemies[i].health <= 0) {
                        enemies[i].active = false;
                    }
                    break;
                }
            }
        }

        // Dispara quando clicar com o bot�o esquerdo do mouse
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && cora.isAlive) {
            ShootProjectile(&projectileW, &cora);
        }

        // Atualiza a posi��o do proj�til (mesmo se inativo faz nada)
        UpdateProjectile(&projectileW);

        BeginDrawing();
        DrawTexture(background1, 0, 0, WHITE);
        drawCora(&cora);
        DrawProjectile(&projectileW);

        // Desenhar cada inimigo
        for (int i = 0; i < MAX_ENEMIES; i++) {
            DrawEnemy(&enemies[i]);
            if (enemies[i].active) {
                // Desenha a vida acima do inimigo
                DrawText(TextFormat("%d", enemies[i].health),
                    enemies[i].position.x + 75,
                    enemies[i].position.y + 40,
                    20,
                    RED);
            }
        }

       

        // *** Aqui que voc� coloca a exibi��o da vida e da mensagem ***
        DrawDebugHitboxes(&cora, enemies, MAX_ENEMIES, showHitboxes);
        DrawText(TextFormat("Vida: %d", cora.health), 10, 10, 20, RED);


        if (!cora.isAlive) {
            DrawText("Cora morreu!", screenWidth / 2 - 80, screenHeight / 2, 30, RED);
        }

        EndDrawing();
    }

    UnloadCoraAnimations(&cora.anims);

    // Descarregar inimigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        UnloadEnemy(&enemies[i]);
    }
    UnloadTexture(magicTex);
    //UnloadTexture(background1);
    CloseWindow();
}
