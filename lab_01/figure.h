#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <fstream>

#include "math.h"
#include "types.h"
#include "file.h"

struct figure_t
{
    bool isLoaded;

    vector4d_t *vertices;
    unsigned int quantityVertices;

    unsigned short *edges;
    unsigned int quantityEdges;
};

figure_t initFigure();

void copyFigureAttributes(figure_t &dst, const figure_t &src);

void newFigureAttributes(figure_t &figure, unsigned int quantityVertices, unsigned int quantityEdges);
//void newFigureAttributes(figure_t &figure, unsigned int quantityVertices, unsigned int quantityEdges);
void deleteFigure(figure_t &figure);

void copyFigure(figure_t &dst, const figure_t &src);

void saveFigureToFile(figure_t &figure, File &fdst);
ERROR saveFigure(figure_t &figure, char *filepath);

ERROR readFigureParameters(unsigned int &quantityVertices, unsigned int &quantityEdges, File &f);

#endif
