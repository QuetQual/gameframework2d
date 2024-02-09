#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "gfc_types.h"
#include "gf2d_sprite.h"
//fake
/**
* entity file thing or something
*/


typedef struct Entity_S
{

	Uint8 _inuse;  //this is the flag that keeps track of memory usage
	Sprite *sprite; //this is the entity's graphic
	float frame;   // the current frame of animation for the sprite
	Vector2D position; //where on the screen things are drawn
	void (*think) (struct Entity_S *self); // func called to make decisions
	void (*update) (struct Entity_S *self); // func called to execute decisions
	void (*free) (struct Entity_S *self); // cleans up custom allocated data
	void *data;							// for ad hoc addition data for entity
	//stopped at 11:20
}Entity;

// @brief this initializes the entity management system and queues up cleanup on exit
// @param max the max number of entities that can exist at once
void entity_system_initialize(Uint32 max);

// @brief clears all active entities
// @param ignore do not clean up this entity
void entity_clear_all(Entity *ignore);

// @brief gets a blank entity for use
// @return NULL on no more room or error, a blank entity otherwise
Entity *entity_new();

// @brief cleans up an entity
// @param self the entity to free
void entity_free(Entity *self);

// @brief run the think functions for active entities
void entity_system_think();

// @brief run the update function for all active entities
void entity_system_update();

// @brief draw all active entities
void entity_system_draw();



#endif

