#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "gfc_types.h"
#include "gf2d_sprite.h"

/**
* entity file thing or something
*/


typedef struct Entity_S
{

	Uint8 _inuse;  //this is the flag that keeps track of memory usage
	Sprite sprite; //this is the entity's graphic
	Vector2D position; //where on the screen things are drawn
	void (*think) (struct Entity_S *self); // func called to make decisions
	void (*update) (struct Entity_S *self); // func called to execute decisions
	void (*free) (struct Entity_S* self); // cleans up custom allocated data
	void* data;							// for ad hoc addition data for entity
	//stopped at 11:20
}Entity;



#endif

