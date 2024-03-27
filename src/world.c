#include "simple_json.h"
#include "simple_logger.h"
#include "enemyentity.h"
#include "player.h" //?
#include "gf2d_graphics.h"
#include "camera.h"
#include "world.h"
#include "platform.h"

// wip
Uint32 spawn_platform_callback(Uint32 interval, void* param); //forward declaration

void spawn_platform(Entity* player)
{
    if (!player) return; // Check if player exists

    // Define position and size for the new platform
    Vector2D platformPosition = vector2d(player->position.x + 75, player->position.y - 100); // Adjust position as needed
    Vector2D platformSize = vector2d(100, 20); // Adjust size as needed

    // Create a blank sprite for the platform
    Sprite* platformSprite = create_blank_sprite(platformSize.x, platformSize.y); // Create a blank sprite

    // Create a new platform entity
    Platform platform = platform_new(platformPosition, platformSize, platformSprite);
}

World* world_test_new(Entity* player)
{
    int width = 75;
    int height = 45;
    int i;
    World* world;

    world = world_new(75, 45);

    if (!world) return NULL;

    world->background = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    world->tileSet = gf2d_sprite_load_all(
        "images/background/tilesetcf.png",
        16,
        16,
        1,
        1);

    if (!world->background || !world->tileSet)
    {
        slog("Failed to load background or tileset image!");
        world_free(world);
        return NULL;
    }

    for (i = 0; i < width; i++)
    {
        world->tileMap[i] = 1;
        world->tileMap[i + ((height * -1) * width)] = 1;
    }
    for (i = 0; i < height; i++)
    {
        world->tileMap[i] = 1;
        world->tileMap[i * width + (width - 1)] = 1;
    }

    // Set up timer to spawn platforms periodically
    SDL_TimerID timerID = SDL_AddTimer(5000, spawn_platform_callback, player);
    if (timerID == 0)
    {
        slog("Failed to set up timer for spawning platforms: %s", SDL_GetError());
    }

    return world;
}

World* world_new(Uint32 width, Uint32 height)
{
    World* world;

    world = gfc_allocate_array(sizeof(World), 1);
    if (!world)
    {
        slog("Failed to allocate a new world");
        return NULL;
    }

    // All defaults
    world->tileMap = gfc_allocate_array(sizeof(Uint8), height * width);
    world->tileHeight = height;
    world->tileWidth = width;

    return world;
}

void world_free(World* world)
{
    if (!world) return;

    gf2d_sprite_free(world->background);
    gf2d_sprite_free(world->tileSet);
    free(world->tileMap);
    free(world);
}

void world_draw(World* world)
{
    int i, j;
    int frame;
    int index;
    Vector2D position;
    if (!world) return;

    gf2d_sprite_draw_image(world->background, vector2d(0, 0));

    if (!world->tileSet) return; // Can't draw when no tiles exist

    for (j = 0; j < world->tileHeight; j++)
    {
        for (i = 0; i < world->tileWidth; i++)
        {
            index = i + ((int)j * (int)world->tileWidth);
            if (world->tileMap[index] == 0) continue;
            position.x = i * world->tileSet->frame_w;
            position.y = j * world->tileSet->frame_h;
            frame = world->tileMap[index] - 1;
            gf2d_sprite_draw(
                world->tileSet,
                position,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                frame);
        }
    }
}

void world_setup_camera(World* world)
{
    if (!world || !world->tileLayer || !world->tileLayer->surface)
    {
        slog("No title layer set for world");
        return;
    }

    camera_set_bounds(gfc_rect(0, 0, world->tileLayer->surface->w, world->tileLayer->surface->h));
}

Uint32 spawn_platform_callback(Uint32 interval, void* param)
{
    Entity* player = (Entity*)param;
    if (!player) return interval; // Check if player exists
    spawn_platform(player); // Spawn a platform near the player
    return interval;  // Repeat the timer
}
        