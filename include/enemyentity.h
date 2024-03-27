#ifndef __ENEMYENTITY_H__
#define __ENEMYENTITY_H__

#include "testentity.h"

/**
 * @brief Creates a new enemy entity.
 * @return A pointer to the newly created enemy entity.
 */
Entity* enemy_new();

void enemy_update(Entity* enemy, Entity* player);

void enemy_draw(Entity* enemy);

#endif
