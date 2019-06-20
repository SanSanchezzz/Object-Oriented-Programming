#include "figure.h"
#include <QDebug>
figure_t initFigure()
{
    figure_t figure;

    figure.isLoaded = false;

    figure.quantityEdges = 0;
    figure.quantityVertices = 0;

    figure.edges = nullptr;
    figure.vertices = nullptr;

    return figure;
}

void copyFigureAttributes(figure_t &dst, const figure_t &src)
{
    for (unsigned int i = 0, len = dst.quantityVertices; i < len; i++)
    {
        dst.vertices[i] = src.vertices[i];
    }

    for (unsigned i = 0, len = dst.quantityEdges; i < len; i++)
    {
        dst.edges[i] = src.edges[i];
    }

    dst.isLoaded = true;
}

void newFigureAttributes(figure_t &figure, unsigned int quantityVertices, unsigned int quantityEdges)
{
    figure.quantityEdges = quantityEdges;
    figure.quantityVertices = quantityVertices;
    figure.vertices = new vector4d_t[quantityVertices];
    figure.edges = new unsigned short[quantityEdges];
    figure.isLoaded = false;
}

void copyFigure(figure_t &dst, const figure_t &src)
{

    dst = initFigure();
    newFigureAttributes(dst, src.quantityVertices, src.quantityEdges);

    copyFigureAttributes(dst, src);
}

void deleteFigure(figure_t &figure)
{
    figure.isLoaded = false;

    figure.quantityEdges = 0;
    figure.quantityVertices = 0;

    if (figure.edges)
    {
        delete [] figure.edges;
        figure.edges = nullptr;
    }

    if (figure.vertices)
    {
        delete [] figure.vertices;
        figure.vertices = nullptr;
    }
}

void saveFigureToFile(figure_t &figure, File &fdst)
{
    writeData(fdst, figure.quantityVertices);
    writeData(fdst, " ");
    writeData(fdst, figure.quantityEdges);
    writeData(fdst, "\n\n");

    for (unsigned i = 0; i < figure.quantityVertices; i++)
    {
        writeData(fdst, figure.vertices[i].x);
        writeData(fdst, " ");
        writeData(fdst, figure.vertices[i].y);
        writeData(fdst, " ");
        writeData(fdst, figure.vertices[i].z);
        writeData(fdst, " ");
    }

    writeData(fdst, "\n");

    for (unsigned i = 0; i < figure.quantityEdges; i += 2)
    {
        writeData(fdst, figure.edges[i]);
        writeData(fdst, " ");
        writeData(fdst, figure.edges[i + 1]);
    }
}

ERROR saveFigure(figure_t &figure, char *filepath)
{
    ERROR result = OK;

    File fdst = initFile();

    result = openFile(fdst, filepath, 'w');

    if (result != OK)
    {
        return result;
    }
    else
    {
        saveFigureToFile(figure, fdst);
    }

    return result;
}

/*
ERROR loadFigure(figure_t &figure, const char *filepath)
{
    ERROR result = OK;

    FILE *fsrc = fopen(filepath, "r");
    if (!fsrc)
    {
        return ERROR::INCORRECT_FILE;
    }

    result = loadFigureFromFile(figure, fsrc);

    fclose(fsrc);

    return result;
}
*/
