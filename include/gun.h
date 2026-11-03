#ifndef GUN_H
#define GUN_H

#include "bullet.h"
#include "raylib.h"
#include "owner.h"

struct Gun
{
    Vector2 position;

    float reloadTime;
    float reloadTimer;
    bool isReloading;

    enum Owner owner;
};

void gunInit(struct Gun *gun, Vector2 position, float reloadTime, enum Owner owner);
void gunShoot(struct Gun *gun, struct Bullet bullets[], int *bulletCount, Vector2 direction);
void gunUpdate(struct Gun *gun, Vector2 position);

#endif