#include "management.h"
#include <QDebug>
ERROR management(controller_t &controller, USER_ACTION action)
{
    ERROR result = OK;

    static figure_t figure = initFigure();

    result = manageTask(figure, controller, action);

    return result;
}

ERROR manageTask(figure_t &figure, controller_t &controller, USER_ACTION action)
{
    ERROR result = OK;

    switch (action)
    {
    case (LOADMODEL):
        result = loadFigureProcess(controller.userInput.file_name, figure);
        break;
    case (SAVEMODEL):
        result = saveFigureProcess(controller.userInput.file_name, figure);
        break;
    case (TRANSPORT):
        result = transportFigureProcess(controller.userInput.transportData, figure);
        break;
    case (SCALE):
        result = scaleFigureProcess(controller.userInput.scaleData, figure);
        break;
    case (ROTATE):
        result = rotateFigureProcess(controller.userInput.rotateData, figure);
        break;
    case (QUIT):
        break;
    }

    if (action != SAVEMODEL || result == OK)
    {
        controller.projectedPoints = getPointsForRender(figure, controller.quantityPoints);
    }

    return result;
}

RESPONSE_ACTION handleProcessResult(char *message, ERROR action)
{
    RESPONSE_ACTION response = RENDER_ACTION;

    switch (action)
    {
    case (OK):
        response = RENDER_ACTION;
        break;
    case (ERROR::INCORRECT_DATA):
        response = ERROR_ACTION;
        strcpy(message, errorMessege::incorrect_data);
        break;
    case (ERROR::INCORRECT_FILE):
        response = ERROR_ACTION;
        strcpy(message, errorMessege::incorrect_file);
        break;
    case (ERROR::FIGURE_NOT_LOADED):
        response = ERROR_ACTION;
        strcpy(message, errorMessege::figure_not_loaded);
        break;
    }

    return response;
}
