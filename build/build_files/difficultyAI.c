#include "DifficultyAI.h"
#include <math.h>

DifficultyAI InitDifficultyAI() {
    return (DifficultyAI){
        .waveNumber = 1,
        .playerHealth = 100,
        .playerMaxHealth = 100,
        .playerDeaths = 0,
        .gameTime = 0,
        .difficultyScore = 1.0f,
        .enemiesSpawnedThisWave = 0
    };
}

void UpdateDifficultyAI(DifficultyAI *ai, int playerHealth, int playerMaxHealth, int playerDeaths, float deltaTime) {
    ai->playerHealth = playerHealth;
    ai->playerMaxHealth = playerMaxHealth;
    ai->playerDeaths = playerDeaths;
    ai->gameTime += deltaTime;

    // Calcula um score de dificuldade (0.5 a 2.0)
    float healthFactor = 1.0f - ((float)playerHealth / playerMaxHealth); // 0 (vida cheia) a 1 (morto)
    float waveFactor = ai->waveNumber * 0.1f;
    float deathPenalty = ai->playerDeaths * -0.2f;
    
    ai->difficultyScore = 0.5f + healthFactor + waveFactor + deathPenalty;
    ai->difficultyScore = Clamp(ai->difficultyScore, 0.5f, 2.0f);
}

int CalculateEnemyCount(const DifficultyAI *ai) {
    // Fórmula base + ajustes dinâmicos
    int baseCount = 3 + (int)(ai->waveNumber * 1.5f);
    
    // Jogador com pouca vida = menos inimigos
    if (ai->playerHealth < ai->playerMaxHealth * 0.3f) {
        baseCount -= 2;
    }
    
    // Wave longa = aumenta gradualmente
    baseCount += (int)(ai->enemiesSpawnedThisWave * 0.1f);
    
    return Clamp(baseCount, 1, 15);
}

void GetEnemyAttributes(const DifficultyAI *ai, int *health, int *damage, float *speed) {
    *health = 50 + (int)(ai->waveNumber * 10 * ai->difficultyScore);
    *damage = 10 + (int)(ai->waveNumber * 2 * ai->difficultyScore);
    *speed = 2.0f * ai->difficultyScore;
}

void DrawDifficultyDebug(const DifficultyAI *ai, int posX, int posY) {
    DrawText(TextFormat("Wave: %d", ai->waveNumber), posX, posY, 20, WHITE);
    DrawText(TextFormat("Dificuldade: %.1f", ai->difficultyScore), posX, posY + 30, 20, WHITE);
    DrawText(TextFormat("Inimigos: %d", CalculateEnemyCount(ai)), posX, posY + 60, 20, WHITE);
}