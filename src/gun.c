#include "gun.h"

void gun_init(struct Gun *gun, Vector2 position, enum Owner owner)
{
    gun->position = position;

    gun->straight_reload_time = 0.3f;
    gun->straight_reload_timer = 0.0f;
    gun->is_straight_reloading = false;

    gun->diagonal_reload_time = 0.5f;
    gun->diagonal_reload_timer = 0.0f;
    gun->is_diagonal_reloading = false;

    gun->owner = owner;
}

bool gun_straight_shoot(struct Gun *gun, struct Bullet *bullet, Vector2 direction)
{
    if (gun->is_straight_reloading)
        return false;

    bullet_init(bullet, gun->position, direction, gun->owner);

    gun->is_straight_reloading = true;

    return true;
}

bool gun_diagonal_shoot(struct Gun *gun, struct Bullet bullets[4])
{
    if (gun->is_diagonal_reloading)
        return false;

    bullet_init(&bullets[0], gun->position, (Vector2){-1, -1}, gun->owner);
    bullet_init(&bullets[1], gun->position, (Vector2){1, 1}, gun->owner);
    bullet_init(&bullets[2], gun->position, (Vector2){-1, 1}, gun->owner);
    bullet_init(&bullets[3], gun->position, (Vector2){1, -1}, gun->owner);

    gun->is_diagonal_reloading = true;

    return true;
}

void gun_update(struct Gun *gun, Vector2 position)
{
    gun->position = position;

    if (gun->is_straight_reloading)
    {
        gun->straight_reload_timer += GetFrameTime();

        if (gun->straight_reload_timer >= gun->straight_reload_time)
        {
            gun->is_straight_reloading = false;
            gun->straight_reload_timer = 0.0f;
        }
    }

    if (gun->is_diagonal_reloading)
    {
        gun->diagonal_reload_timer += GetFrameTime();

        if (gun->diagonal_reload_timer >= gun->diagonal_reload_time)
        {
            gun->is_diagonal_reloading = false;
            gun->diagonal_reload_timer = 0.0f;
        }
    }
}