#include "loadfromfile.h"

void newFigureTransferAttributes(figure_transfer_t &figure, unsigned int quantityVertices, unsigned int quantityEdges)
{
    figure.quantityEdges = quantityEdges;
    figure.quantityVertices = quantityVertices;
    figure.vertices = new vector4d_t[quantityVertices];
    figure.edges = new unsigned short[quantityEdges];
}


void deleteFigureTransfer(figure_transfer_t &figure)
{
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

ERROR readFigureParameters(unsigned int &quantityVertices, unsigned int &quantityEdges, File &f)
{
    ERROR result = OK;

    result = readData(quantityVertices, f);


    if (result != OK)
    {
        return result;
    }

    result = readData(quantityEdges, f);

    if (result != OK)
    {
        return result;
    }
    else if (quantityEdges < 2 || quantityVertices < 2 || quantityEdges % 2 != 0)
    {
        return ERROR::INCORRECT_DATA;
    }

    return OK;
}

ERROR readFigureVertices(figure_transfer_t &figure, File &f)
{
    ERROR result = OK;

    //int flag;

    for (unsigned i = 0, len = figure.quantityVertices; i < len; i++)
    {
        vector4d_t vector;

        result = readData(vector.x, f);
        result = readData(vector.y, f);
        result = readData(vector.z, f);
        //f >> vector.x >> vector.y >> vector.z;

        if (result != OK)
        {

            return result;
        }

        vector.w = 1.0;

        figure.vertices[i] = vector;
    }

    return result;
}

ERROR readFigureEdges(figure_transfer_t &figure, File &f)
{
    ERROR result = OK;

    //int flag;

    for (unsigned i = 0, len = figure.quantityEdges; i < len; i += 2)
    {
        unsigned short id_1, id_2;

        result = readData(id_1, f);
        result = readData(id_2, f);


        //flag = fscanf(f, "%hu%hu", &id_1, &id_2);
        if (result)
        {
            return ERROR::INCORRECT_DATA;
        }

        figure.edges[i] = id_1;
        figure.edges[i + 1] = id_2;
    }

    return result;
}


ERROR loadFigureFromFile(figure_transfer_t &figure, File &fsrc)
{
    ERROR result = OK;

    result = readFigureParameters(figure.quantityVertices, figure.quantityEdges, fsrc);
    if (result != OK)
    {
        return result;
    }

    newFigureTransferAttributes(figure, figure.quantityVertices, figure.quantityEdges);

    result = readFigureVertices(figure, fsrc);
    if (result != OK)
    {
        deleteFigureTransfer(figure);
        return result;
    }

    result = readFigureEdges(figure, fsrc);
    if (result != OK)
    {
        deleteFigureTransfer(figure);
        return result;
    }

    return result;
}

ERROR loadFigure(figure_transfer_t &figure, char *filepath)
{
    ERROR result = OK;

    File fsrc = initFile();

    result = openFile(fsrc, filepath, 'r');

    if (result != OK)
    {
        return result;
    }

    if (!isOpen(fsrc))
    {
        result = ERROR::INCORRECT_FILE;
    }

    result = loadFigureFromFile(figure, fsrc);

    closeFile(fsrc);

    return result;
}

void TransferToFigureAttributes(figure_t &dst, const figure_transfer_t &src)
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

figure_t transferToFigure(figure_transfer_t &figureTransfer)
{
    figure_t figure = initFigure();

    newFigureAttributes(figure, figureTransfer.quantityVertices, figureTransfer.quantityEdges);

    TransferToFigureAttributes(figure, figureTransfer);

    figure.isLoaded = true;

    return figure;
}
