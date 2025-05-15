#include <stdio.h>
#include <raylib.h>
#include "menu.h"
#include "map1.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int buttons(void);
int buttonVoltar(void);

int menu(void)
{
    InitWindow(screenWidth, screenHeight, "The Witch's Journey - Menu");
    SetTargetFPS(60);

    GameState state = MENU;
    float fontSize = screenHeight * 0.04f; // 4% da altura da tela

    while (!WindowShouldClose() && state != EXIT)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (state == MENU) {
            const char* title = "Bem-vindo(a) ao The Witch's Journey!";
            float titleY = screenHeight * 0.1f; // 10% da altura
            DrawText(title, screenWidth / 2 - MeasureText(title, fontSize) / 2, titleY, fontSize, WHITE);

            const char* storyLines[] = {
                "Cora, uma jovem bruxa formada na academia de bruxas, procurou seu",
                "grande mestre Alfred para melhorar sua magia. Ele a envia para uma",
                "jornada na qual ela pode desenvolver suas habilidades de magia e se",
                "tornar a grande bruxa que desde pequena ela sonha em ser.",
                "",
                "O jogador(a) deve guiar Cora em sua jornada para enfrentar seus novos desafios.",
                "Consegue ajudar Cora a se tornar a maior bruxa de sua vila?"
            };

            int numLines = sizeof(storyLines) / sizeof(storyLines[0]);
            float lineSpacing = screenHeight * 0.05f; // 5% da altura
            float startY = screenHeight * 0.25f; // 25% da altura

            for (int i = 0; i < numLines; i++) {
                int textWidth = MeasureText(storyLines[i], fontSize);
                DrawText(storyLines[i], screenWidth / 2 - textWidth / 2, startY + i * lineSpacing, fontSize, WHITE);
            }

            int clicked = buttons();
            if (clicked == 0) {
                state = GAME;
            }
            else if (clicked == 1) {
                state = INSTRUCOES;
            }
            else if (clicked == 2) {
                state = EXIT;
            }
        }

        else if (state == INSTRUCOES) {
            const char* instructions[] = {
                "INSTRUCOES:",
                "",
                "Use as teclas WASD ou as setas do teclado para mover Cora.",
                "Pressione T para atacar.",
                "",
            };

            int numLines = sizeof(instructions) / sizeof(instructions[0]);
            float lineSpacing = screenHeight * 0.05f; // 5% da altura
            float startY = screenHeight * 0.2f; // 20% da altura

            for (int i = 0; i < numLines; i++) {
                int textWidth = MeasureText(instructions[i], fontSize);
                DrawText(instructions[i], screenWidth / 2 - textWidth / 2, startY + i * lineSpacing, fontSize, WHITE);
            }

            if (buttonVoltar()) {
                state = MENU;
            }
        }

        EndDrawing();

        if (state == GAME) {
            CloseWindow();
            map1();
            return 0;
        }
    }

    CloseWindow();
    return 0;
}

int buttons(void) {
    float buttonWidth = screenWidth * 0.25f; // 25% da largura
    float buttonHeight = screenHeight * 0.08f; // 8% da altura
    float buttonX = screenWidth / 2 - buttonWidth / 2;
    float buttonYStart = screenHeight * 0.65f; // 65% da altura

    float buttonSpacing = screenHeight * 0.1f; // 10% da altura

    Rectangle buttons[3];
    for (int i = 0; i < 3; i++) {
        buttons[i] = (Rectangle){ buttonX, buttonYStart + i * buttonSpacing, buttonWidth, buttonHeight };
    }

    const char* labels[] = { "JOGAR", "INSTRUCOES", "SAIR" };
    float buttonFontSize = screenHeight * 0.04f; // 4% da altura

    Vector2 mouse = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        bool hovered = CheckCollisionPointRec(mouse, buttons[i]);
        Color color = hovered ? DARKGRAY : GRAY;

        DrawRectangleRec(buttons[i], color);
        DrawText(labels[i],
            buttonX + buttonWidth / 2 - MeasureText(labels[i], buttonFontSize) / 2,
            buttons[i].y + buttonHeight / 2 - buttonFontSize / 2,
            buttonFontSize,
            WHITE);

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return i;
        }
    }

    return -1;
}

int buttonVoltar(void) {
    float buttonWidth = screenWidth * 0.25f; // 25% da largura
    float buttonHeight = screenHeight * 0.08f; // 8% da altura
    float buttonX = screenWidth / 2 - buttonWidth / 2;
    float buttonY = screenHeight * 0.85f; // 85% da altura

    Rectangle button = { buttonX, buttonY, buttonWidth, buttonHeight };
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, button);
    Color color = hovered ? DARKGRAY : GRAY;

    DrawRectangleRec(button, color);

    const char* label = "VOLTAR";
    float buttonFontSize = screenHeight * 0.04f; // 4% da altura
    DrawText(label,
        buttonX + buttonWidth / 2 - MeasureText(label, buttonFontSize) / 2,
        buttonY + buttonHeight / 2 - buttonFontSize / 2,
        buttonFontSize,
        WHITE);

    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return 1;
    }

    return 0;
}