#include "enemy.h"
#include "config.h"
#include "raymath.h"

void enemy_init(struct Enemy *enemy, enum EnemyType type)
{
    int side = GetRandomValue(0, 3);

    float offset = 20.0f;
    // four spawn sides
    switch (side)
    {
    case 0:
        enemy->position = (Vector2){GetRandomValue(0, WINDOW_WIDTH), offset};
        break;

    case 1:
        enemy->position = (Vector2){GetRandomValue(0, WINDOW_WIDTH), WINDOW_HEIGHT - offset};
        break;

    case 2:
        enemy->position = (Vector2){offset, GetRandomValue(0, WINDOW_HEIGHT)};
        break;

    case 3:
        enemy->position = (Vector2){WINDOW_WIDTH - offset, GetRandomValue(0, WINDOW_HEIGHT)};
        break;
    }

    enemy->type = type;

    switch (type)
    {
    case ENEMY_RED:
        enemy->speed = 150.0f;
        enemy->size = 20.0f;
        enemy->color = RED;
        enemy->health = 3;
        enemy->has_gun = false;
        break;

    case ENEMY_ORANGE:
        enemy->speed = 50.0f;
        enemy->size = 25.0f;
        enemy->color = ORANGE;
        enemy->health = 10;
        enemy->has_gun = false;
        break;
    case ENEMY_GREEN:
        enemy->speed = 50.0f;
        enemy->size = 15.0f;
        enemy->color = GREEN;
        enemy->health = 1;
        enemy->has_gun = true;
        gun_init(&enemy->gun, enemy->position, ENEMY);
        break;
    }

    enemy->is_active = true;
    enemy->line_thickness = 3.0f;

    enemy->hitbox = (Rectangle){
        enemy->position.x - enemy->size,
        enemy->position.y - enemy->size,
        enemy->size * 2,
        enemy->size * 2};
}

void enemy_update(struct Enemy *enemy, Vector2 player_pos)
{
    Vector2 direction = Vector2Normalize(Vector2Subtract(player_pos, enemy->position));
    Vector2 movement = Vector2Scale(direction, enemy->speed * GetFrameTime());

    switch (enemy->type)
    {
    case ENEMY_RED:
        enemy->position = Vector2Add(enemy->position, movement);
        break;

    case ENEMY_ORANGE:
        enemy->position = Vector2Add(enemy->position, movement);
        break;

    case ENEMY_GREEN:
        gun_update(&enemy->gun, enemy->position);
        break;
    }

    enemy->hitbox.x = enemy->position.x - enemy->size;
    enemy->hitbox.y = enemy->position.y - enemy->size;
}

void enemy_draw(const struct Enemy *enemy)
{
    switch (enemy->type)
    {
    case ENEMY_RED:
    {
        Vector2 v1 = {enemy->position.x, enemy->position.y + enemy->size};
        Vector2 v2 = {enemy->position.x - enemy->size, enemy->position.y - enemy->size};
        Vector2 v3 = {enemy->position.x + enemy->size, enemy->position.y - enemy->size};

        DrawLineEx(v1, v2, enemy->line_thickness, enemy->color);
        DrawLineEx(v2, v3, enemy->line_thickness, enemy->color);
        DrawLineEx(v3, v1, enemy->line_thickness, enemy->color);
        break;
    }

    case ENEMY_ORANGE:
    {
        Rectangle rect = {
            enemy->position.x - enemy->size,
            enemy->position.y - enemy->size,
            enemy->size * 2,
            enemy->size * 2};

        DrawRectangleLinesEx(rect, enemy->line_thickness, enemy->color);
        break;
    }

    case ENEMY_GREEN:
    {
        Vector2 v1 = {enemy->position.x, enemy->position.y - enemy->size};
        Vector2 v2 = {enemy->position.x - enemy->size, enemy->position.y};
        Vector2 v3 = {enemy->position.x, enemy->position.y + enemy->size};
        Vector2 v4 = {enemy->position.x + enemy->size, enemy->position.y};

        DrawLineEx(v1, v2, enemy->line_thickness, enemy->color);
        DrawLineEx(v2, v3, enemy->line_thickness, enemy->color);
        DrawLineEx(v3, v4, enemy->line_thickness, enemy->color);
        DrawLineEx(v4, v1, enemy->line_thickness, enemy->color);
        break;
    }
    }
}

void enemy_take_damage(struct Enemy *enemy)
{
    enemy->health -= 1;

    if (enemy->health <= 0)
    {
        enemy->is_active = false;
    }
}