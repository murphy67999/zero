#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enemy.h"
#include "config.h"
#include "bullet.h"

struct Game
{
    struct Player player;
    struct Enemy enemies[MAX_ENEMIES];
    int enemyCount;
    struct Bullet bullets[MAX_BULLETS];
    int bulletCount;
};

void gameRun(struct Game *game);
void gameSpawnBullet(struct Game *game, Vector2 position, Vector2 direction, enum Owner owner);

#endif