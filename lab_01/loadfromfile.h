#ifndef LOADFROMFILE_H
#define LOADFROMFILE_H

#include <iostream>
#include <fstream>

#include "math.h"
#include "types.h"
#include "file.h"
#include "figure.h"

struct figure_transfer_t
{
    vector4d_t *vertices;
    unsigned int quantityVertices;

    unsigned short *edges;
    unsigned int quantityEdges;
};

void newFigureTransferAttributes(figure_transfer_t &figure, unsigned int quantityVertices, unsigned int quantityEdges);
void deleteFigureTransfer(figure_transfer_t &figure);

ERROR loadFigureFromFile(figure_transfer_t &figure, File &fsrc);
ERROR loadFigure(figure_transfer_t &figure, char *filepath);

figure_t transferToFigure(figure_transfer_t &figureTransfer);

#endif // LOADFROMFILE_H
