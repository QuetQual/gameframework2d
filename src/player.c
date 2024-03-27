#include "simple_logger.h"
#include "player.h"
#include "gfc_input.h"

#define GRAVITY 1 // Change as needed
#define JUMP_HEIGHT 10 // Adjust jump height as needed
#define FRAME_RATE 0.1 // Adjust frame rate as needed

void player_handle_input(Entity* self);
void player_apply_gravity(Entity* self);
void player_handle_jump(Entity* self);

Entity* player_new()
{
    Entity* self = entity_new();
    if (!self)
    {
        slog("Failed to spawn player");
        return NULL;
    }

    // Initialize input system
    gfc_input_init("gfc/sample_config/input_new.cfg");

    // Initialize player stats
    self->player_stats.health = 100;
    self->player_stats.movement_speed = 5.0f;
    self->player_stats.gravity_multiplier = 1.0f;

    // Initialize jumping-related variables
    self->jumping = 0;
    self->jump_force = 0;
    self->jump_height = JUMP_HEIGHT; // Adjust as needed
    self->gravity = GRAVITY;   // Adjust as needed

    // Load player sprite
    self->sprite = gf2d_sprite_load_all(
        "images/ed210_top.png",
        128,
        128,
        16,
        0);
    if (!self->sprite)
    {
        slog("Failed to load player sprite");
        entity_free(self);
        return NULL;
    }

    // Set initial position and size
    self->position = vector2d(0.0f, 0.0f);
    self->size = vector2d(128, 128); // Initialize size

    // Set entity functions
    self->think = player_handle_input;
    self->update = player_update;
    self->free = player_free;

    return self;
}

void player_handle_input(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    gfc_input_update();

    Vector2D dir = { 0 };

    if (gfc_input_command_down("walk_left")) dir.x = -1;  // Left
    if (gfc_input_command_down("walk_right")) dir.x = 1; // Right

    // Jumping condition
    if (gfc_input_command_pressed("jump") && !self->jumping)
    {
        self->jumping = 1;
        self->jump_force = JUMP_HEIGHT;
    }

    vector2d_normalize(&dir);
    vector2d_scale(self->velocity, dir, self->player_stats.movement_speed);
}

void player_apply_gravity(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    float GRAV_FINAL = self->gravity * self->player_stats.gravity_multiplier;
    vector2d_add(self->velocity, self->velocity, vector2d(0, GRAV_FINAL));
}

void player_handle_jump(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    if (self->jumping)
    {
        vector2d_add(self->position, self->position, vector2d(0, -self->jump_force));
        self->jump_force--;

        if (self->jump_force <= 0)
        {
            self->jumping = 0;
        }
    }
}

void player_update(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    self->frame += FRAME_RATE;
    if (self->frame >= 16) self->frame = 0;

    player_apply_gravity(self);
    player_handle_jump(self);

    // Update position based on velocity
    vector2d_add(self->position, self->position, self->velocity);
}

void player_free(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    // Free Player-specific data
    // (Currently, there's no specific data allocated for the player)
    entity_free(self);
}
