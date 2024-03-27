#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "testentity.h"
#include "gfc_input.h"

void player_handle_input(Entity* self);

void player_update(Entity* self);

void player_free(Entity* self);

// Spawn a player
// @return NULL on error or a pointer to the player on success
Entity* player_new();

#endif
