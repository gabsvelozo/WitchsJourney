#include <raylib.h>
#include "draw.h"

Texture2D backgroundmenu;
Texture2D backgroundinstrucoes;
Texture2D backgroundraiz;
Texture2D background2;
Texture2D background3;
Texture2D background4;
Texture2D player;
Texture2D enemy;
Texture2D enemy2;
Texture2D enemy3;
Texture2D enemy4;
Texture2D enemy5;
Texture2D enemy6;
Texture2D backgroundleaderboard;

void InitAssets(void) {
	backgroundmenu = LoadTexture("assets/backgroundmenu.png");
	backgroundinstrucoes = LoadTexture("assets/backgroundinstrucoes.png");
    backgroundraiz = LoadTexture("assets/backgroundraiz.png");
    background2 = LoadTexture("assets/background2.png");
    background3 = LoadTexture("assets/background3.png");
    background4 = LoadTexture("assets/background4.png");

    player = LoadTexture("assets/player.png");

    enemy = LoadTexture("assets/enemy.png");
    enemy2 = LoadTexture("assets/enemy2.png");
    enemy3 = LoadTexture("assets/enemy3.png");
    enemy4 = LoadTexture("assets/enemy4.png");
    enemy5 = LoadTexture("assets/enemy5.png");
    enemy6 = LoadTexture("assets/enemy6.png");

	backgroundleaderboard = LoadTexture("assets/backgroundleaderboard.png");
}

void DrawGame(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

	DrawTexture(backgroundmenu, 0, 0, WHITE);
	DrawTexture(backgroundinstrucoes, 0, 0, WHITE);
    DrawTexture(backgroundraiz, 0, 0, WHITE);
	DrawTexture(background2, 0, 0, WHITE);
	DrawTexture(background3, 0, 0, WHITE);
	DrawTexture(background4, 0, 0, WHITE);
	DrawTexture(backgroundleaderboard, 0, 0, WHITE);
    DrawTexture(player, 100, 100, WHITE);
    DrawTexture(enemy, 300, 100, WHITE);
    DrawTexture(enemy2, 350, 100, WHITE);
    DrawTexture(enemy3, 400, 100, WHITE);
    DrawTexture(enemy4, 450, 100, WHITE);
    DrawTexture(enemy5, 500, 100, WHITE);
    DrawTexture(enemy6, 550, 100, WHITE);

    EndDrawing();
}

void UnloadAssets(void) {
	UnloadTexture(backgroundmenu);
	UnloadTexture(backgroundinstrucoes);
    UnloadTexture(backgroundraiz);
    UnloadTexture(background2);
    UnloadTexture(background3);
    UnloadTexture(background4);

    UnloadTexture(player);

    UnloadTexture(enemy);
    UnloadTexture(enemy2);
    UnloadTexture(enemy3);
    UnloadTexture(enemy4);
    UnloadTexture(enemy5);
    UnloadTexture(enemy6);

	UnloadTexture(backgroundleaderboard);
}
