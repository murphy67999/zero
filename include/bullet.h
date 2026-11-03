#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "owner.h"

struct Bullet
{
    struct Vector2 position;
    struct Vector2 direction;
    float speed;

    float size;
    float lineThickness;
    struct Color color;

    float lifeTime;
    float age;
    float isActive;

    enum Owner owner;

    struct Rectangle hitbox;
};

void bulletInit(struct Bullet *bullet, struct Vector2 position, struct Vector2 direction, enum Owner owner);
void bulletUpdate(struct Bullet *bullet);
void bulletDraw(struct Bullet *bullet);

#endif