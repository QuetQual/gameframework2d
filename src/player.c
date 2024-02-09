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

	// Initialize the input system
	gfc_input_init("gfc/sample_config/input_new.cfg");


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

void player_input(Entity* self)
{
	if (!self)
	{
		slog("failed to spawn player");
		return NULL;
	}
	gfc_input_update();
	//const Uint8* keys = SDL_GetKeyboardState(NULL);
	Vector2D dir = { 0 };

	//WORKING c:
	if (gfc_input_command_down("walk_left"))dir.x = -1;  // left
	if (gfc_input_command_down("walk_right"))dir.x = 1; // right
	if (gfc_input_command_down("walk_up"))dir.y = -1; // up
	if (gfc_input_command_down("walk_down"))dir.y = 1;  // down


	vector2d_normalize(&dir);
	vector2d_scale(self->velocity, dir, 3);

}

void player_think(Entity* self)
{
	//Sint32 mx = 0, my = 0; //for mouse based movement
	if (!self)return;
	
	player_input(self);
	
	/*SDL_GetMouseState(&mx, &my); //mouse based movement (not in use anymore)
	if (self->position.x < mx)dir.x = 1;  
	if (self->position.y < my)dir.y = 1;
	if (self->position.x > mx)dir.x = -1;
	if (self->position.y > my)dir.y = -1; */
	
	//vector2d_normalize(&dir);
	//vector2d_scale(self->velocity, dir, 3);
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


