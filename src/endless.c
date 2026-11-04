#include "endless.h"

#include "gun.h"
#include "raymath.h"
#include "array.h"

static void update(struct Endless *game);
static void draw(struct Endless *game);

static void add_bullet(struct Endless *game, struct Bullet bullet);
static void add_enemy(struct Endless *game, struct Enemy enemy);

static void update_player(struct Endless *game);
static void update_bullets(struct Endless *game);
static void update_enemies(struct Endless *game);

static void handle_collisions(struct Endless *game);

static void draw_bullets(const struct Endless *game);
static void draw_enemies(const struct Endless *game);
static void draw_ui(const struct Endless *game);

void endless_init(struct Endless *game)
{
    player_init(&game->player);
    wave_manager_init(&game->wave);
}

void endless_run(struct Endless *game)
{
    update(game);
    draw(game);
}

static void update(struct Endless *game)
{
    update_player(game);
    update_bullets(game);
    update_enemies(game);
    wave_manager_update(&game->wave, game->enemy_count);
    handle_collisions(game);
}

static void draw(struct Endless *game)
{
    ClearBackground(BLACK);

    player_draw(&game->player);
    draw_bullets(game);
    draw_enemies(game);
    draw_ui(game);
}

static void add_bullet(struct Endless *game, struct Bullet bullet)
{
    if (game->bullet_count >= MAX_BULLETS)
        return;

    game->bullets[game->bullet_count] = bullet;

    game->bullet_count++;
}

static void add_enemy(struct Endless *game, struct Enemy enemy)
{
    if (game->enemy_count >= MAX_ENEMIES)
        return;

    game->enemies[game->enemy_count] = enemy;

    game->enemy_count++;
}

static void update_player(struct Endless *game)
{
    player_update(&game->player);
    gun_update(&game->player.gun, game->player.position);

    Vector2 mouse_direction = Vector2Normalize(Vector2Subtract(GetMousePosition(), game->player.position));
    struct Bullet bullet;
    if (gun_straight_shoot(&game->player.gun, &bullet, mouse_direction))
    {
        add_bullet(game, bullet);
    }

    struct Bullet bullets[4];
    if (gun_diagonal_shoot(&game->player.gun, bullets))
    {
        add_bullet(game, bullets[0]);
        add_bullet(game, bullets[1]);
        add_bullet(game, bullets[2]);
        add_bullet(game, bullets[3]);
    }
}

static void update_bullets(struct Endless *game)
{
    for (size_t i = 0; i < game->bullet_count; i++)
    {
        bullet_update(&game->bullets[i]);

        if (!game->bullets[i].is_active)
        {
            array_remove(game->bullets, &game->bullet_count, i, sizeof(struct Bullet));
        }
    }
}

static void update_enemies(struct Endless *game)
{
    struct Enemy enemy;
    if (wave_manager_spawn_enemy(&game->wave, &enemy))
    {
        add_enemy(game, enemy);
    }

    for (size_t i = 0; i < game->enemy_count; i++)
    {
        enemy_update(&game->enemies[i], game->player.position);

        if (game->enemies[i].has_gun)
        {
            Vector2 player_direction = Vector2Normalize(Vector2Subtract(game->player.position, game->enemies[i].position));
            struct Bullet bullet;

            if (gun_straight_shoot(&game->enemies[i].gun, &bullet, player_direction))
            {
                add_bullet(game, bullet);
            }
        }

        if (!game->enemies[i].is_active)
        {
            array_remove(game->enemies, &game->enemy_count, i, sizeof(struct Enemy));
        }
    }
}

static void handle_collisions(struct Endless *game)
{
    for (size_t i = 0; i < game->bullet_count; i++)
    {
        struct Bullet *bullet = &game->bullets[i];

        if (bullet->owner == PLAYER)
        {
            for (size_t j = 0; j < game->enemy_count; j++)
            {
                struct Enemy *enemy = &game->enemies[j];

                if (CheckCollisionRecs(bullet->hitbox, enemy->hitbox))
                {
                    bullet->is_active = false;
                    enemy_take_damage(enemy);
                }
            }
        }

        if (bullet->owner == ENEMY)
        {
            if (CheckCollisionRecs(bullet->hitbox, game->player.hitbox))
            {
                bullet->is_active = false;
                player_take_damage(&game->player);
            }
        }
    }

    for (size_t i = 0; i < game->enemy_count; i++)
    {
        struct Enemy *enemy = &game->enemies[i];

        if (CheckCollisionRecs(enemy->hitbox, game->player.hitbox))
        {
            enemy->is_active = false;
            player_take_damage(&game->player);
        }
    }
}

static void draw_bullets(const struct Endless *game)
{
    for (size_t i = 0; i < game->bullet_count; i++)
    {
        bullet_draw(&game->bullets[i]);
    }
}

static void draw_enemies(const struct Endless *game)
{
    for (size_t i = 0; i < game->enemy_count; i++)
    {
        enemy_draw(&game->enemies[i]);
    }
}

static void draw_ui(const struct Endless *game)
{
    DrawText(TextFormat("Wave: %i", game->wave.current_wave), 10, 10, 30, SKYBLUE);
    DrawText(TextFormat("Enemy Remaining: %i", game->enemy_count), 10, 40, 30, SKYBLUE);
}