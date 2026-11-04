#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "gun.h"

enum EnemyType
{
    ENEMY_RED,
    ENEMY_ORANGE,
    ENEMY_GREEN
};

struct Enemy
{
    Vector2 position;
    float speed;

    float size;
    float line_thickness;
    Color color;

    enum EnemyType type;

    int health;
    Rectangle hitbox;
    bool is_active;

    struct Gun gun;
    bool has_gun;
};

void enemy_init(struct Enemy *enemy, enum EnemyType type);
void enemy_update(struct Enemy *enemy, Vector2 player_pos);
void enemy_draw(const struct Enemy *enemy);
void enemy_take_damage(struct Enemy *enemy);

#endif