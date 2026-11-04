#include "player.h"

#include "config.h"
#include <raymath.h>

void player_init(struct Player *player)
{
    player->position = (Vector2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    player->speed = 200.0f;
    player->size = 20.0f;
    player->line_thickness = 4.0f;
    player->color = SKYBLUE;
    player->health = 10;

    player->hitbox = (Rectangle){
        player->position.x - player->size,
        player->position.y - player->size,
        player->size * 2,
        player->size * 2};

    gun_init(&player->gun, player->position, PLAYER);
}

void player_update(struct Player *player)
{
    float final_speed = player->speed * GetFrameTime();
    if (IsKeyDown(KEY_W))
    {
        player->position.y -= final_speed;
    }
    if (IsKeyDown(KEY_S))
    {
        player->position.y += final_speed;
    }
    if (IsKeyDown(KEY_A))
    {
        player->position.x -= final_speed;
    }
    if (IsKeyDown(KEY_D))
    {
        player->position.x += final_speed;
    }

    player->position.x = Clamp(player->position.x, 0, WINDOW_WIDTH);
    player->position.y = Clamp(player->position.y, 0, WINDOW_HEIGHT);

    player->hitbox.x = player->position.x - player->size;
    player->hitbox.y = player->position.y - player->size;
}

void player_draw(const struct Player *player)
{
    Vector2 v1 = {player->position.x, player->position.y - player->size};
    Vector2 v2 = {player->position.x - player->size, player->position.y + player->size};
    Vector2 v3 = {player->position.x + player->size, player->position.y + player->size};

    DrawLineEx(v1, v2, player->line_thickness, player->color);
    DrawLineEx(v2, v3, player->line_thickness, player->color);
    DrawLineEx(v3, v1, player->line_thickness, player->color);
}

void player_take_damage(struct Player *player)
{
    player->health -= 1;
}