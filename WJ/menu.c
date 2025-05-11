#include <stdio.h>
#include <raylib.h>
#include "menu.h"

int menu(void)
{
    const int screenWidth = 1376;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        int fontSize = screenHeight / 24;
        int lineSpacing = fontSize + 20;

        // Título
        const char* title = "Bem-vindo(a) ao The Witch's Journey!";
        int titleY = screenHeight / 10;
        DrawText(title, screenWidth / 2 - MeasureText(title, fontSize) / 2, titleY, fontSize, WHITE);

        // História
        const char* storyLines[] = {
            "",
            "Cora, uma jovem bruxa formada na academia de bruxas,",
            "procurou seu grande mestre Alfred para melhorar sua magia.",
            "Ele a envia para uma jornada na qual ela pode",
            "desenvolver suas habilidades de magia e se tornar a grande",
            "bruxa que desde pequena ela sonha em ser.",
            "",
            "O jogador(a) deve guiar Cora em sua",
            "jornada para enfrentar seus novos desafios.",
            "Consegue ajudar Cora a se tornar",
            "a maior bruxa de sua vila?"
        };

        int numStoryLines = sizeof(storyLines) / sizeof(storyLines[0]);
        int storyStartY = titleY + fontSize + 20;

        for (int i = 0; i < numStoryLines; i++)
        {
            int textWidth = MeasureText(storyLines[i], fontSize);
            DrawText(storyLines[i], screenWidth / 2 - textWidth / 2, storyStartY + i * lineSpacing, fontSize, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}