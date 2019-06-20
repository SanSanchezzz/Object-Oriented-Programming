#include "graphics.h"
#include <QDebug>


/*vector2i_t converToRast(vector4d_t &vector, int screenWidth, int screenHeight, double kx)
{
    vector2i_t result;

    result.x = (int)(vector.x * (screenWidth - 1) / 2 + (screenWidth - 1) / 2);
    result.y = (int)(vector.y * (screenHeight - 1) / 2 + (screenHeight - 1) / 2);

    return result;
}*/

vector2i_t converToRast(vector4d_t &vector, int screenWidth, int screenHeight, double kx)
{
    vector2i_t result;

    result.x = (int) (vector.x * 10 + screenWidth / 2);
    result.y = (int) (-vector.y * 10 + screenHeight / 2);

    return result;
}

vector4d_t pointProjection(const vector4d_t &point, const matrix4d_t &projectionMatrix)
{
    vector4d_t result;

    result = multiplyVectorByMatrix(point, projectionMatrix);

    result.x /= result.z;
    result.y /= result.z;
    qDebug() << "zzz" << result.x << result.y << result.z;
    return result;
}
