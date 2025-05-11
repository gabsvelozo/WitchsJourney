#include <stdio.h>
#include <raylib.h>
#include "menu.h"
#include "map1.h"

typedef enum {
    MENU,
    GAME,
    INSTRUCOES,
    EXIT
} GameState;

const int screenWidth = 1820;
const int screenHeight = 1000;

int buttons(void);
int buttonVoltar(void);

int menu(void)
{
    InitWindow(screenWidth, screenHeight, "The Witch's Journey - Menu");
    SetTargetFPS(60);

    GameState state = MENU;
    int fontSize = 30;

    while (!WindowShouldClose() && state != EXIT)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (state == MENU) {
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
                "Use as setas <- -> para mover Cora.",
                "Pressione W para atacar.",
                "Use ESPACO para pular.",
                "",
            };

            int numLines = sizeof(instructions) / sizeof(instructions[0]);
            int lineSpacing = 40;
            int startY = 200;

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
    const int buttonWidth = 300;
    const int buttonHeight = 60;
    const int buttonX = screenWidth / 2 - buttonWidth / 2;
    const int buttonYStart = 650;
    const int buttonSpacing = 80;

    Rectangle buttons[3];
    for (int i = 0; i < 3; i++) {
        buttons[i] = (Rectangle){ buttonX, buttonYStart + i * buttonSpacing, buttonWidth, buttonHeight };
    }

    const char* labels[] = { "JOGAR", "INSTRUCOES", "SAIR" };

    Vector2 mouse = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        bool hovered = CheckCollisionPointRec(mouse, buttons[i]);
        Color color = hovered ? DARKGRAY : GRAY;

        DrawRectangleRec(buttons[i], color);
        DrawText(labels[i],
            buttonX + buttonWidth / 2 - MeasureText(labels[i], 30) / 2,
            buttons[i].y + 15,
            30,
            WHITE);

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return i;
        }
    }

    return -1;
}

int buttonVoltar(void) {
    const int buttonWidth = 300;
    const int buttonHeight = 60;
    const int buttonX = screenWidth / 2 - buttonWidth / 2;
    const int buttonY = 650;

    Rectangle button = { buttonX, buttonY, buttonWidth, buttonHeight };
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, button);
    Color color = hovered ? DARKGRAY : GRAY;

    DrawRectangleRec(button, color);

    const char* label = "VOLTAR";
    DrawText(label,
        buttonX + buttonWidth / 2 - MeasureText(label, 30) / 2,
        buttonY + 15,
        30,
        WHITE);

    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return 1;
    }

    return 0;
}
