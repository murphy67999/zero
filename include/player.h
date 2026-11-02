#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct Player
{
    Vector2 position;
    float speed;
};

void playerInit(struct Player *player);
void playerUpdate(struct Player *player);
void playerDraw(struct Player *player);

#endif