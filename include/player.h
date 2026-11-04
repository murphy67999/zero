#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "gun.h"

struct Player
{
    Vector2 position;
    float speed;

    float line_thickness;
    Color color;
    float size;

    struct Gun gun;
    int health;

    Rectangle hitbox;
};

void player_init(struct Player *player);
void player_update(struct Player *player);
void player_draw(const struct Player *player);
void player_take_damage(struct Player *player);

#endif