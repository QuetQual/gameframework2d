#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gfc_vector.h"
#include "gfc_types.h" 
#include "gfc_shape.h"

typedef struct
{
    Vector2D position;
    Vector2D size;
    Rect bounds; //
    Bool bindCamera;
} Camera;

// @brief get the camera's pos in world space
// @return the position
Vector2D camera_get_position();

// @brief get the offset to draw things relative to the camera
// @the offset
Vector2D camera_get_offset();

// @brief set the camera's position in world space
void camera_set_position(Vector2D position);

// @brief enable/disable camera binding to bounds
// @param bindCamera: true to bind camera to bounds, false otherwise
void camera_enable_binding(Bool bindCamera);

// @brief set the camera bounds
// @param bounds: rectangle defining camera bounds
void camera_set_bounds(Rect bounds);

// @brief apply camera bounds to keep it within the defined limits
void camera_apply_bounds();

// @brief center the camera on a specific position
// @param target: position to center the camera on
void camera_center_on(Vector2D target);

#endif
