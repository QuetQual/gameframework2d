#include "simple_logger.h"
#include "enemyentity.h"
#include "gfc_types.h"
#include "gfc_vector.h"

// Include the function to exit the game
extern void exit_game();

Entity* enemy_new()
{
    Entity* enemy = entity_new();
    if (!enemy)
    {
        slog("Failed to create enemy entity");
        return NULL;
    }

    // Load enemy sprite
    enemy->sprite = gf2d_sprite_load_all(
        "images/space_bug.png",
        32, // frame width
        32, // frame height
        10,
        0);

    if (!enemy->sprite)
    {
        slog("Failed to load enemy sprite");
        entity_free(enemy);
        return NULL;
    }

    // Set initial position and size
    enemy->position = vector2d(0.0f, 0.0f);
    enemy->size = vector2d(32.0f, 32.0f);

    return enemy;
}

void enemy_update(Entity* enemy, Entity* player)
{
    if (!enemy || !player)
    {
        slog("Enemy or player entity is NULL");
        return;
    }

    // Calculate direction vector from enemy to player
    Vector2D direction;
    vector2d_sub(direction, player->position, enemy->position);
    vector2d_normalize(&direction);

    // Adjust speed as needed
    float speed = 1.0f;

    // Move enemy along the direction vector
    vector2d_scale(enemy->velocity, direction, speed);

    // Update enemy position based on velocity
    vector2d_add(enemy->position, enemy->position, enemy->velocity);

    // Simple collision detection with player
    if (vector2d_magnitude_between(player->position, enemy->position) < 20) // Adjust collision radius as needed
    {
        // Enemy collided with player, close the game
        slog("Enemy collided with player! Game Over!");
        exit(0); // Call function to exit the game
    }
}

void enemy_draw(Entity* enemy)
{
    if (!enemy || !enemy->sprite)
    {
        slog("Enemy or enemy sprite is NULL");
        return;
    }

    // Render enemy sprite at its position
    gf2d_sprite_render(
        enemy->sprite,
        enemy->position,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        (Uint32)enemy->frame
    );
}
