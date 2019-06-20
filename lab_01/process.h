#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"
#include "controller.h"
#include "figure.h"
#include "figure_transformer.h"
#include "loadfromfile.h"

void resetSources(figure_t &figure);

ERROR loadFigureProcess(char *fileName, figure_t &figure);
ERROR saveFigureProcess(char *fileName, figure_t &figure);
ERROR transportFigureProcess(transportData_t transportData, figure_t &figure);
ERROR scaleFigureProcess(scaleData_t scaleData, figure_t &figure);
ERROR rotateFigureProcess(rotateData_t rotateData, figure_t &figure);

#endif // PROCESS_H
