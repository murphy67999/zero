#ifndef GUN_H
#define GUN_H

#include "bullet.h"
#include "raylib.h"
#include "owner.h"

struct Gun
{
    Vector2 position;

    float straight_reload_time;
    float straight_reload_timer;
    bool is_straight_reloading;

    float diagonal_reload_time;
    float diagonal_reload_timer;
    bool is_diagonal_reloading;

    enum Owner owner;
};

void gun_init(struct Gun *gun, Vector2 position, enum Owner owner);
bool gun_straight_shoot(struct Gun *gun, struct Bullet *bullet, Vector2 direction);
bool gun_diagonal_shoot(struct Gun *gun, struct Bullet bullets[4]);
void gun_update(struct Gun *gun, Vector2 position);

#endif