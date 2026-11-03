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
    struct Bullet bullets[MAX_BULLETS];
};

void gameRun(struct Game *game);

#endif