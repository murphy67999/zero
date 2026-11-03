#include "game.h"
#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "config.h"
#include "raymath.h"
#include "array.h"
#include "bullet.h"

void gameRun(struct Game *game)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "zero");
    SetTargetFPS(60);

    playerInit(&game->player);

    float spawnTimer = 0.0f;
    float spawnInterval = 2.0f;

    int enemyCount = 0;
    int bulletCount = 0;

    Texture2D background = LoadTexture("assets/background.png");
    Color tint = ColorAlpha(WHITE, 0.1f);

    while (!WindowShouldClose())
    {
        // collisions
        for (int i = 0; i < bulletCount; i++)
        {
            struct Bullet *bullet = &game->bullets[i];

            if (bullet->owner == PLAYER)
            {
                for (int j = 0; j < enemyCount; j++)
                {
                    struct Enemy *enemy = &game->enemies[j];

                    if (CheckCollisionRecs(bullet->hitbox, enemy->hitbox))
                    {
                        bullet->isActive = false;
                        enemyTakeDamage(enemy);
                    }
                }
            }

            if (bullet->owner == ENEMY)
            {
                if (CheckCollisionRecs(bullet->hitbox, game->player.hitbox))
                {
                    bullet->isActive = false;
                    playerTakeDamage(&game->player);
                }
            }
        }

        for (int i = 0; i < enemyCount; i++)
        {
            struct Enemy *enemy = &game->enemies[i];

            if (CheckCollisionRecs(enemy->hitbox, game->player.hitbox))
            {
                enemy->isActive = false;
                playerTakeDamage(&game->player);
            }
        }

        for (int i = 0; i < bulletCount; i++)
        {
            bulletUpdate(&game->bullets[i]);

            if (!game->bullets[i].isActive)
            {
                arrayRemove(game->bullets, &bulletCount, i, sizeof(struct Bullet));
            }
        }

        for (int i = 0; i < enemyCount; i++)
        {
            enemyUpdate(&game->enemies[i], game->player.position);

            if (!game->enemies[i].isActive)
            {
                arrayRemove(game->enemies, &enemyCount, i, sizeof(struct Enemy));
                continue;
            }

            if (game->enemies[i].hasGun)
            {
                Vector2 bulletDir = Vector2Normalize(Vector2Subtract(game->player.position, game->enemies[i].position));
                gunShoot(&game->enemies[i].gun, game->bullets, &bulletCount, bulletDir);
            }
        }

        playerUpdate(&game->player);

        Vector2 bulletDir = Vector2Normalize(Vector2Subtract(GetMousePosition(), game->player.position));
        gunShoot(&game->player.gun, game->bullets, &bulletCount, bulletDir);

        // spawn
        spawnTimer += GetFrameTime();
        if (spawnTimer >= spawnInterval)
        {
            enemySpawn(game->enemies, &enemyCount);
            spawnTimer = 0.0f;
        }

        // draw
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(background, 0, 0, tint);

        playerDraw(&game->player);
        for (int i = 0; i < enemyCount; i++)
        {
            enemyDraw(&game->enemies[i]);
        }
        for (int i = 0; i < bulletCount; i++)
        {
            bulletDraw(&game->bullets[i]);
        }

        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
}