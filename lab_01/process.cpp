#include "process.h"
#include <QDebug>

ERROR loadFigureProcess(char *fileName, figure_t &figure)
{
    ERROR result = OK;

    figure_transfer_t transferFigure;

    result = loadFigure(transferFigure, fileName);

    if (result == OK)
    {
        deleteFigure(figure);

        figure = transferToFigure(transferFigure);

        deleteFigureTransfer(transferFigure);
    }
    else

    deleteFigureTransfer(transferFigure);

    return result;
}

ERROR saveFigureProcess(char *filePath, figure_t &figure)
{
    ERROR result = OK;

    if (figure.isLoaded)
    {
        result = saveFigure(figure, filePath);
    }
    else
    {
        result = ERROR::FIGURE_NOT_LOADED;
    }

    return result;
}

ERROR transportFigureProcess(transportData_t transportData, figure_t &figure)
{
    ERROR result = OK;

    if (figure.isLoaded)
    {
        vector3d_t transport = { transportData.dx,
                                 transportData.dy,
                                 transportData.dz };
        transportFigure(figure, transport);

    }
    else
    {
        result = ERROR::FIGURE_NOT_LOADED;
    }

    return result;
}

ERROR scaleFigureProcess(scaleData_t scaleData, figure_t &figure)
{
    ERROR result = OK;

    if (figure.isLoaded)
    {
        vector3d_t scale = { scaleData.kx,
                             scaleData.ky,
                             scaleData.kz };
        scaleFigure(figure, scale);
        //controller.projectedPoints = getPointsForRender(figure, controller.quantityPoints);
    }
    else
    {
        result = ERROR::FIGURE_NOT_LOADED;
    }

    return result;
}

ERROR rotateFigureProcess(rotateData_t rotateData, figure_t &figure)
{
    ERROR result = OK;

    if (figure.isLoaded)
    {
        vector3d_t rotate = { rotateData.alphax,
                              rotateData.alphay,
                              rotateData.alphaz };
        rotateFigure(figure, rotate);
        //controller.projectedPoints = getPointsForRender(figure, controller.quantityPoints);
    }
    else
    {
        result = ERROR::FIGURE_NOT_LOADED;
    }

    return result;
}

void resetSources(figure_t &figure)
{
    deleteFigure(figure);
    //resetController(controller);
}
