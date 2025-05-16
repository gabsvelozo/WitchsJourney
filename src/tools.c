#include "raylib.h"
#include "tools.h"

void DrawDebugHitboxes(Cora* cora, Enemy* enemies, int enemyCount, bool show) {
    if (!show) return;

    // Cora
    DrawRectangleLines(
        (int)cora->hitbox.x,
        (int)cora->hitbox.y,
        (int)cora->hitbox.width,
        (int)cora->hitbox.height,
        GREEN
    );

    // Inimigos
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].active) {
            DrawRectangleLines(
                (int)enemies[i].hitbox.x,
                (int)enemies[i].hitbox.y,
                (int)enemies[i].hitbox.width,
                (int)enemies[i].hitbox.height,
                RED
            );
        }
    }

    DrawText("DEBUG: Hitboxes ON (H para esconder)", 10, 40, 20, GREEN);
}
