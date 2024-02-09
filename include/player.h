#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "testentity.h"
#include "gfc_input.h"

typedef struct
{
	//stats
	int health;
	float move_speed;
	float gravity_multiplier;
} Player;

//@brief spawn a player
// @return NULL on error or a pointer to the player on success
Entity* player_new();




#endif