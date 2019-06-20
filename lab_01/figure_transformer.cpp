#include "figure_transformer.h"
#include <QDebug>
vector4d_t *getPointsForRender(const figure_t &figure, unsigned int &count)
{
    vector4d_t *points = nullptr;

    count = figure.quantityEdges;

    points = new vector4d_t[count];

    const matrix4d_t projection = createProjectionMatrix(0.001, 1000.0, 4.0 / 3.0, 60.0);

    for (unsigned int i = 0; i < count; i += 2)
    {
        vector4d_t lineStart;
        vector4d_t lineEnd;
        int idxStart;
        int idxEnd;

        idxStart = figure.edges[i];
        idxEnd = figure.edges[i + 1];

        lineStart = figure.vertices[idxStart];
        lineEnd = figure.vertices[idxEnd];

        lineStart = pointProjection(lineStart, projection);
        lineEnd = pointProjection(lineEnd, projection);

        points[i] = lineStart;
        points[i + 1] = lineEnd;
    }

    return points;
}

void transportFigure(figure_t &figure, const vector3d_t &vectorTransport)
{
    matrix4d_t transport = createTransportMatrix(vectorTransport);

    for (unsigned i = 0, len = figure.quantityVertices; i < len; i++)
    {
        figure.vertices[i] = multiplyVectorByMatrix(figure.vertices[i], transport);
    }
}

void scaleFigure(figure_t &figure, const vector3d_t &vectorScale)
{
    matrix4d_t scale = createScaleMatrix(vectorScale);

    for (unsigned i = 0, len = figure.quantityVertices; i < len; i++)
    {
        figure.vertices[i] = multiplyVectorByMatrix(figure.vertices[i], scale);
    }
}

void rotateFigure(figure_t &figure, const vector3d_t &vectorRotate)
{
    matrix4d_t rotateX = createRotateXMatrix(vectorRotate.x);
    matrix4d_t rotateY = createRotateYMatrix(vectorRotate.y);
    matrix4d_t rotateZ = createRotateZMatrix(vectorRotate.z);
    matrix4d_t rotateM;

    rotateM = multiplyMatrices(rotateX, rotateY);
    rotateM = multiplyMatrices(rotateM, rotateZ);

    for (unsigned i = 0, len = figure.quantityVertices; i < len; i++)
    {
        figure.vertices[i] = multiplyVectorByMatrix(figure.vertices[i], rotateM);
    }
}
