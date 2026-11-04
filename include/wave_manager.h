#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include <stdbool.h>
#include <stddef.h>

struct WaveManager
{
    int current_wave;

    int red_remaining;
    int orange_remaining;
    int green_remaining;

    bool is_wave_active;
};

struct Enemy;

void wave_manager_init(struct WaveManager *wave);
void wave_manager_update(struct WaveManager *wave, size_t enemy_count);
bool wave_manager_spawn_enemy(struct WaveManager *wave, struct Enemy *enemy);

#endif