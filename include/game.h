#ifndef GAME_H
#define GAME_H

#include "player.h"

struct Game
{
    struct Player player;
};

void gameRun(struct Game *game);
void gameInit(struct Game *game);
void gameUpdate(struct Game *game);
void gameDraw(struct Game *game);

#endif