#include "controller.h"

controller_t createController()
{
    controller_t newController;

    newController.userInput.transportData.dx = 0.0;
    newController.userInput.transportData.dy = 0.0;
    newController.userInput.transportData.dz = 0.0;

    newController.userInput.scaleData.kx = 0.0;
    newController.userInput.scaleData.ky = 0.0;
    newController.userInput.scaleData.kz = 0.0;

    newController.userInput.rotateData.alphax = 0.0;
    newController.userInput.rotateData.alphay = 0.0;
    newController.userInput.rotateData.alphaz = 0.0;

    newController.quantityPoints = 0;

    newController.projectedPoints = nullptr;

    return newController;
}

void resetController(controller_t &controller)
{
    if (controller.projectedPoints)
    {
        controller.quantityPoints = 0;

        delete [] controller.projectedPoints;
    }
}
