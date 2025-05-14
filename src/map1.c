#include "raylib.h"
#include "cora.h"

extern const int screenWidth;
extern const int screenHeight;

void map1(void) {
    InitWindow(screenWidth, screenHeight, "Mapa 1");
    InitAudioDevice(); // se usar sons
    SetTargetFPS(60);

    Texture2D background1 = LoadTexture("resources/assets/background1.png");

    Cora cora = initCora();

    while (!WindowShouldClose()) {
        updateCora(&cora);

        BeginDrawing();
        DrawTexture(background1, 0, 0, WHITE);
        drawCora(&cora);
        EndDrawing();
    }

    unloadCora(&cora);
    UnloadTexture(background1);
    CloseWindow();
}
