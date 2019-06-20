#ifndef MATH_H
#define MATH_H

#include <cmath>

struct vector4d_t
{
    double x;
    double y;
    double z;
    double w;
};

struct vector3d_t
{
    double x;
    double y;
    double z;
};

struct vector2i_t
{
    int x;
    int y;
};

struct matrix4d_t
{
    double value[4][4];
};

inline double toRadians(double degrees) { return (double)(degrees * M_PI / 1800); }

vector4d_t multiplyVectorByMatrix(const vector4d_t &vecror, const matrix4d_t &matrix);
matrix4d_t multiplyMatrices(const matrix4d_t &left, const matrix4d_t &right);

matrix4d_t initMatrix(double diagonalElement);
matrix4d_t createProjectionMatrix(double zNear, double zFar, double aspect, double fov);
matrix4d_t createTransportMatrix(const vector3d_t& translate);
matrix4d_t createScaleMatrix(const vector3d_t& scale);
matrix4d_t createRotateXMatrix(double angle);
matrix4d_t createRotateYMatrix(double angle);
matrix4d_t createRotateZMatrix(double angle);

#endif // MATH_H
