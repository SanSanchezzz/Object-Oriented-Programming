#include "math.h"
#include <QDebug>

vector4d_t multiplyVectorByMatrix(const vector4d_t &v, const matrix4d_t &m)
{
    vector4d_t res;

    res.x = v.x * m.value[0][0] + v.y * m.value[1][0] +
        v.z * m.value[2][0] + v.w * m.value[3][0];

    res.y = v.x * m.value[0][1] + v.y * m.value[1][1] +
        v.z * m.value[2][1] + v.w * m.value[3][1];

    res.z = v.x * m.value[0][2] + v.y * m.value[1][2] +
        v.z * m.value[2][2] + v.w * m.value[3][2];

    res.w = v.x * m.value[0][3] + v.y * m.value[1][3] +
        v.z * m.value[2][3] + v.w * m.value[3][3];

    return res;
}

matrix4d_t multiplyMatrices(const matrix4d_t &left, const matrix4d_t &right)
{
    matrix4d_t result = initMatrix(1.0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            double sum = 0.0;

            for (int k = 0; k < 4; k++)
            {
                sum += left.value[i][k] * right.value[k][j];
            }

            result.value[i][j] = sum;
        }
    }

    return result;
}

matrix4d_t  initMatrix(double diagonalElement)
{
    matrix4d_t matrix;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                matrix.value[i][j] = diagonalElement;
            }
            else
            {
                matrix.value[i][j] = 0;
            }
        }
    }

    return matrix;
}

matrix4d_t createProjectionMatrix(double zNear, double zFar, double aspect, double fov)
{
    matrix4d_t matrix;
    double zRange;
    double tanHalfFOV;

    matrix = initMatrix(1.0);
    zRange = zNear - zFar;
    tanHalfFOV = tan(toRadians(fov / 2.0));

    matrix.value[0][0] = 1.0 / (tanHalfFOV * aspect);
    matrix.value[0][1] = 0.0;
    matrix.value[0][2] = 0.0;
    matrix.value[0][3] = 0.0;

    matrix.value[1][0] = 0.0;
    matrix.value[1][1] = 1.0 / tanHalfFOV;
    matrix.value[1][2] = 0.0;
    matrix.value[1][3] = 0.0;

    matrix.value[2][0] = 0.0;
    matrix.value[2][1] = 0.0;
    matrix.value[2][2] = (-zNear - zFar) / zRange;
    matrix.value[2][3] = 2.0 * zFar * zNear / zRange;

    matrix.value[3][0] = 0.0;
    matrix.value[3][1] = 0.0;
    matrix.value[3][2] = 1.0;
    matrix.value[3][3] = 0.0;

    return matrix;
}

matrix4d_t createTransportMatrix(const vector3d_t &translate)
{
    matrix4d_t result = initMatrix(1.0);

    result.value[3][0] = translate.x;
    result.value[3][1] = translate.y;
    result.value[3][2] = translate.z;

    return result;
}

matrix4d_t createScaleMatrix(const vector3d_t &scale)
{
    matrix4d_t result = initMatrix(1.0);

    result.value[0][0] = scale.x;
    result.value[1][1] = scale.y;
    result.value[2][2] = scale.z;

    return result;
}

matrix4d_t createRotateXMatrix(double angle)
{
    matrix4d_t result = initMatrix(1.0);

    angle = toRadians(angle);

    result.value[1][1] = cos(angle);
    result.value[1][2] = sin(angle);
    result.value[2][1] = -sin(angle);
    result.value[2][2] = cos(angle);

    return result;
}

matrix4d_t createRotateYMatrix(double angle)
{
    matrix4d_t result = initMatrix(1.0);

    angle = toRadians(angle);

    result.value[0][0] = cos(angle);
    result.value[0][2] = sin(angle);
    result.value[2][0] = -sin(angle);
    result.value[2][2] = cos(angle);

    return result;
}

matrix4d_t createRotateZMatrix(double angle)
{
    matrix4d_t result = initMatrix(1.0);

    angle = toRadians(angle);

    result.value[0][0] = cos(angle);
    result.value[0][1] = sin(angle);
    result.value[1][0] = -sin(angle);
    result.value[1][1] = cos(angle);

    return result;
}
