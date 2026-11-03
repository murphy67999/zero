#include "player.h"

void playerInit(struct Player *player)
{
    player->position = (Vector2){200.0f, 100.0f};
    player->speed = 200.0f;
    player->size = 20.0f;
    player->lineThickness = 4.0f;
    player->color = SKYBLUE;
    player->health = 10;

    player->hitbox = (Rectangle){
        player->position.x - player->size,
        player->position.y - player->size,
        player->size * 2,
        player->size * 2};

    gunInit(&player->gun, player->position, PLAYER);
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

    gunUpdate(&player->gun, player->position);

    player->hitbox.x = player->position.x - player->size;
    player->hitbox.y = player->position.y - player->size;
}

void playerDraw(struct Player *player)
{
    Vector2 v1 = {player->position.x, player->position.y - 20};
    Vector2 v2 = {player->position.x - 20, player->position.y + 20};
    Vector2 v3 = {player->position.x + 20, player->position.y + 20};

    DrawLineEx(v1, v2, player->lineThickness, player->color);
    DrawLineEx(v2, v3, player->lineThickness, player->color);
    DrawLineEx(v3, v1, player->lineThickness, player->color);

    DrawText(TextFormat("Health: %i", player->health), 20, 20, 30, SKYBLUE);
}

void playerTakeDamage(struct Player *player)
{
    player->health -= 1;
}