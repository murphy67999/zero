#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "gun.h"

struct Player
{
    struct Vector2 position;
    float speed;

    float lineThickness;
    struct Color color;
    float size;

    struct Gun gun;

    struct Rectangle hitbox;
    int health;
};

void playerInit(struct Player *player);
void playerUpdate(struct Player *player);
void playerDraw(struct Player *player);
void playerTakeDamage(struct Player *player);

#endif