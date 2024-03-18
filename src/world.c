#include "simple_json.h"
#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "camera.h"
#include "world.h"

World* world_test_new()
{
	int width = 75;
	int height = 45;
	int i;
	World* world;

	world = world_new(75, 45);

	if (!world)return NULL;
	world->background = gf2d_sprite_load_image("images/backgrounds/bg_flat.png"); //something wrong with this - no background loading...
	world->tileSet = gf2d_sprite_load_all(
		"images/background/tilesetcf.png",
		16,
		16,
		1,
		1);

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
	return world;
}

World* world_new(Uint32 width, Uint32 height)
{

	World* world;

	world = gfc_allocate_array(sizeof(World), 1);
	if (!world)
	{
		slog("failed to allocate a new world"); 
		return NULL;
	}
	//boilerplate code here
	//all defaults
	world->tileMap = gfc_allocate_array(sizeof(Uint8), height * width);
	world->tileHeight = height;
	world->tileWidth = width;
	return world;
}


void world_free(World* world)
{
	if (!world)return NULL;

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
	if (!world)return;
	gf2d_sprite_draw_image(world->background, vector2d(0, 0));
	if (!world->tileSet)return; //cant draw when no tiles exist
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


void world_setup_camera(World *world)
{
	if (!world) return;
	if ((!world->tileLayer) || (!world->tileLayer->surface))
	{
		slog("no title layer set for world");
		return;
	}
	camera_set_bounds(gfc_rect(0, 0, world->tileLayer->surface->w, world->tileLayer->surface->h));

}