#include <SDL.h>
#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gfc_input.h"
#include "camera.h"
#include "world.h"
#include "player.h"
#include "testentity.h"
#include "gfc_vector.h"

void update_camera_position(Entity* player) {
    if (!player) return;

    Vector2D resolution = gf2d_graphics_get_resolution();
    Vector2D cameraFocusPosition;
    cameraFocusPosition.x = player->position.x + player->size.x / 2;
    cameraFocusPosition.y = player->position.y + player->size.y / 2;

    Vector2D cameraOffset;
    cameraOffset.x = resolution.x / 2 - cameraFocusPosition.x;
    cameraOffset.y = resolution.y / 2 - cameraFocusPosition.y;

    Vector2D currentCameraPosition = camera_get_position();
    Vector2D newCameraPosition;
    newCameraPosition.x = currentCameraPosition.x + cameraOffset.x;
    newCameraPosition.y = currentCameraPosition.y + cameraOffset.y;

    camera_set_position(newCameraPosition);
}

int main(int argc, char* argv[]) {
    int done = 0;
    const Uint8* keys;
    Sprite* sprite = NULL;
    World* world = NULL;
    int mx, my;
    float mf = 0;
    Sprite* mouse = NULL;
    Color mouseColor = gfc_color8(255, 255, 105, 200);
    Entity* player = NULL;

    init_logger("gf2d.log", 0);
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize("gf2d", 1200, 720, 1200, 720, vector4d(0, 0, 0, 255), 0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(5024);
    SDL_ShowCursor(SDL_DISABLE);

    sprite = gf2d_sprite_load_image("images/backgrounds/egg.png");
    mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16, 0);

    player = player_new();
    if (!player) {
        slog("Failed to initialize player!");
        return -1;
    }

    world = world_test_new(player);

    if (!world || !sprite || !mouse) {
        slog("Failed to initialize world, sprite, or mouse!");
        return -1;
    }

    while (!done) {
        Uint32 max = 1024; //attempt number who even knows to fix the crashing
        entity_system_initialize(max);
        keys = SDL_GetKeyboardState(NULL);

        entity_update(player);
        update_camera_position(player);

        camera_apply_bounds();
        world_draw(world);
        entity_draw(player);

        SDL_GetMouseState(NULL, NULL);

        if (keys[SDL_SCANCODE_ESCAPE]) done = 1;

        SDL_PumpEvents();
        keys = SDL_GetKeyboardState(NULL);
        SDL_GetMouseState(&mx, &my);
        mf += 0.1;
        if (mf >= 16.0) mf = 0;

        gf2d_graphics_clear_screen();
        gf2d_sprite_draw_image(sprite, vector2d(0, 0)); // Draw background

        // Other drawing logic here if needed

        // Draw UI elements
        gf2d_sprite_draw(mouse, vector2d(mx, my), NULL, NULL, NULL, NULL, &mouseColor, (int)mf);

        gf2d_graphics_next_frame();

        if (keys[SDL_SCANCODE_ESCAPE]) done = 1;
    }

    entity_free(player);
    world_free(world);
    slog("---==== END ====---");

    return 0;
}
