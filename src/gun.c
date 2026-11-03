#include "gun.h"

#include "config.h"

void gunInit(struct Gun *gun, Vector2 position, float reloadTime, enum Owner owner)
{
    gun->position = position;
    gun->reloadTime = reloadTime;
    gun->reloadTimer = 0.0f;
    gun->isReloading = false;
    gun->owner = owner;
}

void gunShoot(struct Gun *gun, struct Bullet bullets[], int *bulletCount, Vector2 direction)
{
    if (*bulletCount >= MAX_BULLETS || gun->isReloading)
        return;

    bulletInit(&bullets[*bulletCount], gun->position, direction, gun->owner);

    gun->isReloading = true;

    (*bulletCount)++;
}

void gunUpdate(struct Gun *gun, Vector2 position)
{
    gun->position = position;

    if (!gun->isReloading)
        return;

    gun->reloadTimer += GetFrameTime();

    if (gun->reloadTimer >= gun->reloadTime)
    {
        gun->isReloading = false;
        gun->reloadTimer = 0.0f;
    }
}