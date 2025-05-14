#include <raylib.h>
#include "draw.h"

extern const int screenWidth;
extern const int screenHeight;

void map1(void)
{
    InitWindow(screenWidth, screenHeight, "Mapa 1");
    InitAssets();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background1, 0, 0, WHITE);
        EndDrawing();
    }

    UnloadAssets();
    CloseWindow();
}