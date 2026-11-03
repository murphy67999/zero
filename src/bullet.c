#include "bullet.h"

#include "raymath.h"

void bulletInit(struct Bullet *bullet, Vector2 position, Vector2 direction, enum Owner owner)
{
    bullet->position = position;
    bullet->direction = direction;
    bullet->speed = 500.0f;
    bullet->size = 5.0f;
    bullet->lineThickness = 2.0f;
    bullet->lifeTime = 2.0f;
    bullet->age = 0.0f;
    bullet->isActive = true;
    bullet->owner = owner;

    if (bullet->owner == PLAYER)
    {
        bullet->color = WHITE;
    }
    if (bullet->owner == ENEMY)
    {
        bullet->color = RED;
    }

    bullet->hitbox = (Rectangle){
        bullet->position.x - bullet->size,
        bullet->position.y - bullet->size,
        bullet->size * 2,
        bullet->size * 2};
}

void bulletUpdate(struct Bullet *bullet)
{
    Vector2 movement = Vector2Scale(bullet->direction, bullet->speed * GetFrameTime());

    bullet->position = Vector2Add(bullet->position, movement);

    bullet->age += GetFrameTime();

    if (bullet->age >= bullet->lifeTime)
        bullet->isActive = false;

    bullet->hitbox.x = bullet->position.x - bullet->size;
    bullet->hitbox.y = bullet->position.y - bullet->size;
}

void bulletDraw(struct Bullet *bullet)
{
    Vector2 v1 = {bullet->position.x, bullet->position.y - bullet->size};
    Vector2 v2 = {bullet->position.x - bullet->size, bullet->position.y + bullet->size};
    Vector2 v3 = {bullet->position.x + bullet->size, bullet->position.y + bullet->size};

    DrawLineEx(v1, v2, bullet->lineThickness, bullet->color);
    DrawLineEx(v2, v3, bullet->lineThickness, bullet->color);
    DrawLineEx(v3, v1, bullet->lineThickness, bullet->color);
}