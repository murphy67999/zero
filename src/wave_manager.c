#include "wave_manager.h"

#include <math.h>

#include "enemy.h"

static void wave_manager_generate_wave(struct WaveManager *wave);

void wave_manager_init(struct WaveManager *wave)
{
    wave->current_wave = 1;
    wave->is_wave_active = false;
}

void wave_manager_update(struct WaveManager *wave, size_t enemy_count)
{
    if (!wave->is_wave_active)
    {
        wave_manager_generate_wave(wave);
        wave->is_wave_active = true;
    }

    if (wave->red_remaining == 0 &&
        wave->orange_remaining == 0 &&
        wave->green_remaining == 0 &&
        enemy_count == 0)
    {
        wave->current_wave += 1;
        wave->is_wave_active = false;
    }
}

bool wave_manager_spawn_enemy(struct WaveManager *wave, struct Enemy *enemy)
{
    if (wave->red_remaining > 0)
    {
        enemy_init(enemy, ENEMY_RED);
        wave->red_remaining--;
    }

    else if (wave->orange_remaining > 0)
    {
        enemy_init(enemy, ENEMY_ORANGE);
        wave->orange_remaining--;
    }

    else if (wave->green_remaining > 0)
    {
        enemy_init(enemy, ENEMY_GREEN);
        wave->green_remaining--;
    }
    else
    {
        return false;
    }

    return true;
}

static void wave_manager_generate_wave(struct WaveManager *wave)
{
    wave->red_remaining = 5 + wave->current_wave * 2;
    wave->orange_remaining = 1 + wave->current_wave;
    wave->green_remaining = wave->current_wave / 2;
}