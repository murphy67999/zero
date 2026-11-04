#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "owner.h"

struct Bullet
{
    Vector2 position;
    Vector2 direction;
    float speed;

    float size;
    float line_thickness;
    Color color;

    float lifetime;
    float age;
    bool is_active;
    enum Owner owner;

    Rectangle hitbox;
};

void bullet_init(struct Bullet *bullet, Vector2 position, Vector2 direction, enum Owner owner);
void bullet_update(struct Bullet *bullet);
void bullet_draw(const struct Bullet *bullet);

#endif