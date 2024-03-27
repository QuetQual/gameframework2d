#ifndef __WORLD_H__
#define __WORLD_H__

#include "gf2d_sprite.h"
#include "gfc_vector.h"
#include "gfc_input.h"
#include "testentity.h"
#include "player.h"

typedef struct
{
    Sprite* background;
    Sprite* tileSet;
    Sprite* tileLayer;
    Uint8* tileMap;
    Uint8* tileHeight;
    Uint8* tileWidth;
    Vector2D playerPosition;
    Vector2D enemyPosition;
} World;

World* world_test_new();

//@brief allocate a new world
//@return NULL on error, or a blank world
World* world_new();

//@brief free a world
//@return world the world to free
void world_free(World* world);

/* @brief draw the world
  @return world the world to draw */
void world_draw(World* world);

/* @brief spawns a platform
  @return platform spawned */
void spawn_platform(Entity* player);

#endif
