#include "bullet.h"

#include "raymath.h"

void bullet_init(struct Bullet *bullet, Vector2 position, Vector2 direction, enum Owner owner)
{
    bullet->position = position;
    bullet->direction = direction;
    bullet->speed = 500.0f;
    bullet->size = 5.0f;
    bullet->line_thickness = 2.0f;
    bullet->lifetime = 2.0f;
    bullet->age = 0.0f;
    bullet->is_active = true;
    bullet->owner = owner;

    switch (bullet->owner)
    {
    case PLAYER:
        bullet->color = WHITE;
        break;

    case ENEMY:
        bullet->color = RED;
        break;
    }

    bullet->hitbox = (Rectangle){
        bullet->position.x - bullet->size,
        bullet->position.y - bullet->size,
        bullet->size * 2,
        bullet->size * 2};
}

void bullet_update(struct Bullet *bullet)
{
    Vector2 movement = Vector2Scale(bullet->direction, bullet->speed * GetFrameTime());

    bullet->position = Vector2Add(bullet->position, movement);

    bullet->age += GetFrameTime();

    if (bullet->age >= bullet->lifetime)
        bullet->is_active = false;

    bullet->hitbox.x = bullet->position.x - bullet->size;
    bullet->hitbox.y = bullet->position.y - bullet->size;
}

void bullet_draw(const struct Bullet *bullet)
{
    Vector2 v1 = {bullet->position.x, bullet->position.y - bullet->size};
    Vector2 v2 = {bullet->position.x - bullet->size, bullet->position.y + bullet->size};
    Vector2 v3 = {bullet->position.x + bullet->size, bullet->position.y + bullet->size};

    DrawLineEx(v1, v2, bullet->line_thickness, bullet->color);
    DrawLineEx(v2, v3, bullet->line_thickness, bullet->color);
    DrawLineEx(v3, v1, bullet->line_thickness, bullet->color);
}