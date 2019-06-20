#ifndef FIGURE_TRANSFORMER_H
#define FIGURE_TRANSFORMER_H

#include "math.h"
#include "figure.h"
#include "graphics.h"

vector4d_t *getPointsForRender(const figure_t &figure, unsigned int &count);

void transportFigure(figure_t &figure, const vector3d_t &vectorTransport);
void scaleFigure(figure_t &figure, const vector3d_t &vectorScale);
void rotateFigure(figure_t &figure, const vector3d_t &vectorRotate);
#endif // FIGURE_TRANSFORMER_H
