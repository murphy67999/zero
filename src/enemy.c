#include "enemy.h"
#include "config.h"
#include "raymath.h"

void enemyInit(struct Enemy *enemy)
{
    enemy->position = (Vector2){GetRandomValue(0, WINDOW_WIDTH), GetRandomValue(0, WINDOW_HEIGHT)};

    int random = GetRandomValue(1, 3);

    switch (random)
    {
    case 1:
        enemy->type = ENEMY_TRIANGLE;
        enemy->speed = 200.0f;
        enemy->size = 20.0f;
        enemy->color = RED;
        enemy->health = 3;
        enemy->hasGun = false;
        break;

    case 2:
        enemy->type = ENEMY_SQUARE;
        enemy->speed = 50.0f;
        enemy->size = 25.0f;
        enemy->color = ORANGE;
        enemy->health = 10;
        enemy->hasGun = false;
        break;
    case 3:
        enemy->type = ENEMY_DIAMOND;
        enemy->speed = 50.0f;
        enemy->size = 15.0f;
        enemy->color = GREEN;
        enemy->health = 2;
        enemy->hasGun = true;
        gunInit(&enemy->gun, enemy->position, ENEMY);
        break;
    }
    enemy->isActive = true;
    enemy->lineThickness = 3.0f;

    enemy->hitbox = (Rectangle){
        enemy->position.x - enemy->size,
        enemy->position.y - enemy->size,
        enemy->size * 2,
        enemy->size * 2};
}

void enemySpawn(struct Enemy enemies[], int *enemyCount)
{
    if (*enemyCount >= MAX_ENEMIES)
        return;

    enemyInit(&enemies[*enemyCount]);

    (*enemyCount)++;
}

void enemyUpdate(struct Enemy *enemy, Vector2 playerPos)
{
    Vector2 direction = Vector2Normalize(Vector2Subtract(playerPos, enemy->position));
    Vector2 movement = Vector2Scale(direction, enemy->speed * GetFrameTime());

    switch (enemy->type)
    {
    case ENEMY_TRIANGLE:
        enemy->position = Vector2Add(enemy->position, movement);
        break;

    case ENEMY_SQUARE:
        enemy->position = Vector2Add(enemy->position, movement);
        break;

    case ENEMY_DIAMOND:
        gunUpdate(&enemy->gun, enemy->position);
        break;
    }

    enemy->hitbox.x = enemy->position.x - enemy->size;
    enemy->hitbox.y = enemy->position.y - enemy->size;
}

void enemyDraw(struct Enemy *enemy)
{
    switch (enemy->type)
    {
    case ENEMY_TRIANGLE:
    {
        Vector2 v1 = {enemy->position.x, enemy->position.y + enemy->size};
        Vector2 v2 = {enemy->position.x - enemy->size, enemy->position.y - enemy->size};
        Vector2 v3 = {enemy->position.x + enemy->size, enemy->position.y - enemy->size};

        DrawLineEx(v1, v2, enemy->lineThickness, enemy->color);
        DrawLineEx(v2, v3, enemy->lineThickness, enemy->color);
        DrawLineEx(v3, v1, enemy->lineThickness, enemy->color);
        break;
    }

    case ENEMY_SQUARE:
    {
        struct Rectangle rect = {
            enemy->position.x - enemy->size,
            enemy->position.y - enemy->size,
            enemy->size * 2,
            enemy->size * 2};

        DrawRectangleLinesEx(rect, enemy->lineThickness, enemy->color);
        break;
    }

    case ENEMY_DIAMOND:
    {
        Vector2 v1 = {enemy->position.x, enemy->position.y - enemy->size};
        Vector2 v2 = {enemy->position.x - enemy->size, enemy->position.y};
        Vector2 v3 = {enemy->position.x, enemy->position.y + enemy->size};
        Vector2 v4 = {enemy->position.x + enemy->size, enemy->position.y};

        DrawLineEx(v1, v2, enemy->lineThickness, enemy->color);
        DrawLineEx(v2, v3, enemy->lineThickness, enemy->color);
        DrawLineEx(v3, v4, enemy->lineThickness, enemy->color);
        DrawLineEx(v4, v1, enemy->lineThickness, enemy->color);
        break;
    }
    }
}

void enemyTakeDamage(struct Enemy *enemy)
{
    enemy->health -= 1;

    if (enemy->health <= 0)
    {
        enemy->isActive = false;
    }
}