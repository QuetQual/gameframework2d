#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gf2d_sprite.h"

/**
* entity file thing or something
*/

typedef struct Entity_S
{
    Uint8 _inuse;               // Flag that keeps track of memory usage
    Sprite* sprite;             // Entity's graphic
    float frame;                // Current frame of animation for the sprite
    Vector2D position;          // Position of the entity
    Vector2D size;              // Size of the entity
    Vector2D velocity;          // Velocity of the entity
    void (*think)(struct Entity_S* self);    // Function called to make decisions
    void (*update)(struct Entity_S* self);   // Function called to execute decisions
    void (*free)(struct Entity_S* self);     // Function to clean up custom allocated data
    void (*handle_input)(struct Entity_S* self); // Function for entity movement
    void* data;                 // Additional data for the entity

    // Player-specific stats
    struct
    {
        int health;
        float movement_speed;
        float gravity_multiplier;
    } player_stats;

    // Additional fields for jumping
    Uint8 jumping;              // Jump flag
    float jump_force;           // Jump force
    float jump_height;          // Maximum jump height
    float gravity;              // Gravity strength
} Entity;

// Function prototypes
void entity_system_initialize(Uint32 max);
void entity_clear_all(Entity* ignore);
Entity* entity_new();
void entity_free(Entity* self);
void entity_system_think();
void entity_system_update();
void entity_system_draw();

#endif // __ENTITY_H__
