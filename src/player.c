#include "simple_logger.h"

#include "player.h"
#include "gfc_input.h"

#define GRAVITY 1 // change as needed
#define JUMP_HEIGHT 10 // adjust jump height as needed

void player_think(Entity* self);
void player_update(Entity* self);
void player_free(Entity* self);

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

    // Initialize Player stats
    self->player_stats.health = 100;
    self->player_stats.movement_speed = 5.0f;
    self->player_stats.gravity_multiplier = 1.0f;

    // Initialize jumping-related variables
    self->jumping = 0;
    self->jump_force = 0;
    self->jump_height = 10.0f; // Adjust as needed
    self->gravity = GRAVITY;   // Adjust as needed

    self->sprite = gf2d_sprite_load_all(
        "images/ed210_top.png",
        128,
        128,
        16,
        0);
    self->frame = 0;
    self->position = vector2d(0, 0);

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
        return;
    }

    gfc_input_update();

    Vector2D dir = { 0 };

    if (gfc_input_command_down("walk_left")) dir.x = -1;  // left
    if (gfc_input_command_down("walk_right")) dir.x = 1; // right

    // Jumping condition
    if (gfc_input_command_pressed("jump") && !self->jumping)
    {
        self->jumping = 1;
        self->jump_force = JUMP_HEIGHT;
    }

    vector2d_normalize(&dir);
    vector2d_scale(self->velocity, dir, self->player_stats.movement_speed);
}


void player_think(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    // Access playerData->health, playerData->move_speed, etc.
    player_input(self);
}

void player_update(Entity* self)
{
    if (!self)
    {
        slog("Player is NULL");
        return;
    }

    self->frame += 0.1;
    if (self->frame >= 16) self->frame = 0;

    // Apply gravity
    float GRAV_FINAL = GRAVITY * self->player_stats.gravity_multiplier;
    vector2d_add(self->velocity, self->velocity, vector2d(0, GRAV_FINAL));

    // Jumping logic
    if (self->jumping)
    {
        vector2d_add(self->position, self->position, vector2d(0, -self->jump_force));
        self->jump_force--;

        if (self->jump_force <= 0)
        {
            self->jumping = 0;
        }
    }

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
    if (self->data)
    {
        free(self->data);
        self->data = NULL;
    }
}
