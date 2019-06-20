
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "math.h"
/*
struct userInput_t
{
    double dx;
    double dy;
    double dz;

    double kx;
    double ky;
    double kz;

    double alphax;
    double alphay;
    double alphaz;

    char *file_name;
};

struct controller_t
{
    userInput_t userInput;

    vector4d_t *projectedPoints;
    unsigned int quantityPoints;

};
*/

struct transportData_t
{
    double dx;
    double dy;
    double dz;
};

struct scaleData_t
{
    double kx;
    double ky;
    double kz;
};

struct rotateData_t
{
    double alphax;
    double alphay;
    double alphaz;
};

union userInput_t
{

    transportData_t transportData;

    scaleData_t scaleData;

    rotateData_t rotateData;

    char *file_name;
};

struct controller_t
{
    userInput_t userInput;

    vector4d_t *projectedPoints;
    unsigned int quantityPoints;

};


controller_t createController();
void resetController(controller_t &controller);

#endif // CONTROLLER_H
