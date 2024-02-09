#include "simple_logger.h"

#include "player.h"
#include "gfc_input.h"

#define GRAVITY 1 // change as needed

void player_think(Entity *self);
void player_update(Entity *self);
void player_free(Entity *self);


Entity* player_new()
{
	Entity* self;
	self = entity_new();
	if (!self)
	{
		slog("failed to spawn player");
		return NULL;
	}
	self->sprite = gf2d_sprite_load_all(
		"images/ed210_top.png",
		128,
		128,
	    16,
		0);
	self->frame = 0; 
	self->position = vector2d(0,0); 

	self->think = player_think;
	self->update = player_update;
	self->free = player_free;

	return self;
}

void player_think(Entity* self)
{
	Vector2D dir = { 0 };
	Sint32 mx = 0, my = 0;
	if (!self)return; 

	
	if (gfc_input_key_down(SDL_SCANCODE_A))dir.x = -1; // left
	if (gfc_input_key_down(SDL_SCANCODE_D))dir.x = 1; // right
	
	
	/*
	SDL_GetMouseState(&mx, &my); //mouse based movement (not in use anymore)
	if (self->position.x < mx)dir.x = 1;  
	if (self->position.y < my)dir.y = 1;
	if (self->position.x > mx)dir.x = -1;
	if (self->position.y > my)dir.y = -1; 
	vector2d_normalize(&dir); */

	vector2d_scale(self->velocity, dir, 3);
}

void player_update(Entity* self)
{
	if (!self)return;
	self->frame += 0.1;
	if (self->frame >= 16)self->frame = 0;

	//attempt #1 at "gravity" - works fine for the most part
	vector2d_add(self->velocity, self->velocity, vector2d(0, GRAVITY));

	//update pos based on velo
	vector2d_add(self->position, self->position, self->velocity);
}

void player_free(Entity* self)
{
	if (!self)return;
}


