#include "gun.h"

#include "game.h"

void gunInit(struct Gun *gun, Vector2 position, enum Owner owner)
{
    gun->position = position;

    gun->straightReloadTime = 0.3f;
    gun->straightReloadTimer = 0.0f;
    gun->isStraightReloading = false;

    gun->diagonalReloadTime = 1.0f;
    gun->diagonalReloadTimer = 0.0f;
    gun->isDiagonalReloading = false;

    gun->owner = owner;
}

void gunStraightShoot(struct Gun *gun, struct Game *game, Vector2 direction)
{
    if (gun->isStraightReloading)
        return;

    gameSpawnBullet(game, gun->position, direction, gun->owner);

    gun->isStraightReloading = true;
}

void gunDiagonalShoot(struct Gun *gun, struct Game *game)
{
    if (gun->isDiagonalReloading)
        return;

    gameSpawnBullet(game, gun->position, (Vector2){-1, -1}, gun->owner);
    gameSpawnBullet(game, gun->position, (Vector2){1, -1}, gun->owner);
    gameSpawnBullet(game, gun->position, (Vector2){-1, 1}, gun->owner);
    gameSpawnBullet(game, gun->position, (Vector2){1, 1}, gun->owner);

    gun->isDiagonalReloading = true;
}

void gunUpdate(struct Gun *gun, Vector2 position)
{
    gun->position = position;

    if (gun->isStraightReloading)
    {
        gun->straightReloadTimer += GetFrameTime();

        if (gun->straightReloadTimer >= gun->straightReloadTime)
        {
            gun->isStraightReloading = false;
            gun->straightReloadTimer = 0.0f;
        }
    }

    if (gun->isDiagonalReloading)
    {
        gun->diagonalReloadTimer += GetFrameTime();

        if (gun->diagonalReloadTimer >= gun->diagonalReloadTime)
        {
            gun->isDiagonalReloading = false;
            gun->diagonalReloadTimer = 0.0f;
        }
    }
}