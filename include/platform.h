#ifndef PLATFORM_H
#define PLATFORM_H

#include "gf2d_sprite.h"
#include "gfc_vector.h"
#include "testentity.h" 

typedef struct
{
    Vector2D position;
    Vector2D size;
    Sprite* sprite;
} Platform;

/**
 * @brief Create a new platform entity
 * @param position The position of the platform
 * @param size The size of the platform
 * @param sprite The sprite for the platform
 * @return Platform* The created platform entity.
 */
Platform platform_new(Vector2D position, Vector2D size, Sprite* sprite);

/**
 * @brief Draw the platform entity.
 * @param platform The platform entity to draw
 */
void platform_draw(Platform* platform);

/**
 * @brief Check collision between an entity and a platform
 * @param entity The entity to check collision for
 * @param platform The platform to check collision with
 * @return int 1 if there is a collision, 0 else
 */
int check_collision(Entity* entity, Platform* platform);

#endif
