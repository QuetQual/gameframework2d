#include "platform.h"
#include "gfc_vector.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"

Platform platform_new(Vector2D position, Vector2D size, Sprite* sprite)
{
    Platform platform;
    platform.position = position;
    platform.size = size;
    platform.sprite = sprite;
    return platform;
}

void platform_draw(Platform* platform)
{
    if (!platform)
    {
        //slog("Cannot draw platform: platform is NULL");
        return;
    }

    if (platform->sprite)
    {
        gf2d_sprite_draw(
            platform->sprite,
            platform->position,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            0
        );
    }
}

int check_collision(Entity* entity, Platform* platform)
{
    if (!entity || !platform)
    {
        //slog("Cannot check collision: entity or platform is NULL");
        return 0;
    }

    SDL_Rect entityRect = {
        (int)entity->position.x,
        (int)entity->position.y,
        (int)entity->size.x,
        (int)entity->size.y
    };
    SDL_Rect platformRect = {
        (int)platform->position.x,
        (int)platform->position.y,
        (int)platform->size.x,
        (int)platform->size.y
    };

    if (SDL_HasIntersection(&entityRect, &platformRect))
    {
        return 1; // Collision detected
    }

    return 0; // No collision
}

Sprite* create_blank_sprite(int width, int height)
{
    Sprite* sprite = NULL;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (!surface)
    {
        //slog("Failed to create surface for blank sprite: %s", SDL_GetError());
        return NULL;
    }

    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 255, 255)); // should make a white rectangle
    sprite = gf2d_sprite_load_image("black_rectangle", surface); // 
    if (!sprite)
    {
        //slog("Failed to create blank sprite: %s", SDL_GetError());
        SDL_FreeSurface(surface); //memory
        return NULL;
    }

    return sprite;
}
