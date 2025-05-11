#include <stdio.h>
#include <raylib.h>
#include "menu.h"

int menu(void)
{
    const int screenWidth = 1820;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        int fontSize = 30;

        const char* title = "Bem-vindo(a) ao The Witch's Journey!";
        DrawText(title, screenWidth / 2 - MeasureText(title, fontSize) / 2, 100, fontSize, WHITE);

        const char* storyLines[] = {
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

        int numLines = sizeof(storyLines) / sizeof(storyLines[0]);
        int lineSpacing = 40;
        int startY = 180;

        for (int i = 0; i < numLines; i++)
        {
            int textWidth = MeasureText(storyLines[i], fontSize);
            DrawText(storyLines[i], screenWidth / 2 - textWidth / 2, startY + i * lineSpacing, fontSize, WHITE);
        }

        const char* instructions[] = {
            "Aperte ENTER para iniciar",
            "ou ESC para sair.",
            "Use as setas de direita e esquerda para se mover",
            "Use a tecla W para atacar",
            "e a barra de espaco para pular!"
        };

        int instructionStartY = 700;

        for (int i = 0; i < 5; i++)
        {
            int textWidth = MeasureText(instructions[i], fontSize);
            DrawText(instructions[i], screenWidth / 2 - textWidth / 2, instructionStartY + i * lineSpacing, fontSize, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
