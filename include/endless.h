#ifndef ENDLESS_H
#define ENDLESS_H

#include "player.h"
#include "enemy.h"
#include "config.h"
#include <stddef.h>
#include "wave_manager.h"

struct Endless
{
    struct Player player;

    struct Enemy enemies[MAX_ENEMIES];
    size_t enemy_count;

    struct Bullet bullets[MAX_BULLETS];
    size_t bullet_count;

    struct WaveManager wave;
};

void endless_init(struct Endless *game);
void endless_run(struct Endless *game);

#endif