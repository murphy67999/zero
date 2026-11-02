#include "player.h"

void playerInit(struct Player *player)
{
    player->position = (Vector2){200.0f, 100.0f};
    player->speed = 200.0f;
}

void playerUpdate(struct Player *player)
{
    float finalSpeed = player->speed * GetFrameTime();
    if (IsKeyDown(KEY_W))
    {
        player->position.y -= finalSpeed;
    }
    if (IsKeyDown(KEY_S))
    {
        player->position.y += finalSpeed;
    }
    if (IsKeyDown(KEY_A))
    {
        player->position.x -= finalSpeed;
    }
    if (IsKeyDown(KEY_D))
    {
        player->position.x += finalSpeed;
    }
}

void playerDraw(struct Player *player)
{
    DrawCircleV(player->position, 30, PURPLE);
}