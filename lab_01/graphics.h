#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "math.h"

vector2i_t converToRast(vector4d_t &vector, int screenWidth, int screenHeight, double kx);

vector4d_t pointProjection(const vector4d_t &point, const matrix4d_t &projectionMatrix);

#endif // GRAPHICS_H
