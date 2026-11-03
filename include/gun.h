#ifndef GUN_H
#define GUN_H

#include "bullet.h"
#include "raylib.h"
#include "owner.h"

struct Gun
{
    Vector2 position;

    float straightReloadTime;
    float straightReloadTimer;
    bool isStraightReloading;

    float diagonalReloadTime;
    float diagonalReloadTimer;
    bool isDiagonalReloading;

    enum Owner owner;
};

struct Game;

void gunInit(struct Gun *gun, Vector2 position, enum Owner owner);
void gunStraightShoot(struct Gun *gun, struct Game *game, Vector2 direction);
void gunDiagonalShoot(struct Gun *gun, struct Game *game);
void gunUpdate(struct Gun *gun, Vector2 position);

#endif