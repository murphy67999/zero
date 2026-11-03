#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "gun.h"

enum EnemyType
{
    ENEMY_TRIANGLE,
    ENEMY_SQUARE,
    ENEMY_DIAMOND
};

struct Enemy
{
    struct Vector2 position;
    float speed;

    float size;
    float lineThickness;
    struct Color color;

    enum EnemyType type;

    int health;
    struct Rectangle hitbox;
    bool isActive;

    struct Gun gun;
    bool hasGun;
};

void enemyInit(struct Enemy *enemy);
void enemySpawn(struct Enemy enemies[], int *enemyCount);
void enemyUpdate(struct Enemy *enemy, Vector2 playerPos);
void enemyDraw(struct Enemy *enemy);
void enemyTakeDamage(struct Enemy *enemy);

#endif