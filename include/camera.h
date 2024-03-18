#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gfc_vector.h"

//;-;

// @brief get the camera's pos in world space
// @return the position
Vector2D camera_get_position();

// @brief get the offset to draw things relative to the camera
// @the offset
Vector2D camera_get_offset();

// @brief set the camera's position in world space
// 
void camera_set_position(Vector2D position);

//
//
void camera_enable_binding(Bool bindCamera);

//
//
void camera_set_bounds(Rect bounds);

void camera_center_on(Vector2D target); // stopped camera video at 25:50


#endif