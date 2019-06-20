#include "canvas.h"
#include <QDebug>
Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    this->xMax = +5;
    this->xMin = -5;
    this->yMax = +5;
    this->yMin = -5;

    this->xRange = this->xMax - this->xMin;
    this->yRange = this->yMax - this->yMin;

    this->imageOffset = 50;
}

void Canvas::setScalingK()
{
    double kx = (this->width() - 2 * this->imageOffset) / (this->xRange);
    double ky = (this->height() - 2 * this->imageOffset) / (this->yRange);

    this->scalingK = fmin(kx, ky);
}

Canvas::~Canvas()
{
}

void Canvas::getPoints(vector4d_t * pP, unsigned qP)
{
    Canvas::projectedPoints = pP;
    Canvas::quantityPoints = qP;
}

double Canvas::xCartToDisp(double xC)
{
    return this->imageOffset + (xC * this->scalingK);
}

double Canvas::yCartToDisp(double yC)
{
    return this->imageOffset - (yC * this->scalingK);
}

void Canvas::setDisplayRange()
{
    double maxX = converToRast(Canvas::projectedPoints[0], this->width(), this->height(), this->scalingK).x;
    double minX = converToRast(Canvas::projectedPoints[0], this->width(), this->height(), this->scalingK).x;
    double maxY = converToRast(Canvas::projectedPoints[0], this->width(), this->height(), this->scalingK).y;
    double minY = converToRast(Canvas::projectedPoints[0], this->width(), this->height(), this->scalingK).y ;

    for (unsigned i = 0, len = Canvas::quantityPoints; i < len; i += 2)
    {

        vector2i_t lineBegin = converToRast(Canvas::projectedPoints[i], this->width(), this->height(), this->scalingK);
        vector2i_t lineEnd = converToRast(Canvas::projectedPoints[i + 1], this->width(), this->height(), this->scalingK);

        if (maxX < lineBegin.x)
        {
            maxX = lineBegin.x;
        }
        if (minX > lineBegin.x)
        {
            minX = lineBegin.x;
        }

        if (maxY < lineBegin.y)
        {
            maxY = lineBegin.y;
        }
        if (minY > lineBegin.y)
        {
            minY = lineBegin.y;
        }
        if (maxX < lineEnd.x)
        {
            maxX = lineEnd.x;
        }
        if (minX > lineEnd.x)
        {
            minX = lineEnd.x;
        }

        if (maxY < lineEnd.y)
        {
            maxY = lineEnd.y;
        }
        if (minY > lineEnd.y)
        {
            minY = lineEnd.y;
        }
    }

    this->xMax = maxX;
    this->xMin = minX;
    this->yMax = maxY;
    this->yMin = minY;

    this->xRange = this->xMax - this->xMin;
    this->yRange = this->yMax - this->yMin;
}

void Canvas::draw()
{
    double rOffSet;
    double xRangePossible;

    double yRangePossible;
    QPainter painter(this);

    double dx, dy;

    dx = this->width() / 2;
    dy = this->height() / 2;

    painter.fillRect(0, 0, this->width(), this->height(), this->BGColor);

    painter.setPen(MyColors::red);

    xRangePossible = (this->width() - 2 * this->imageOffset) / this->scalingK;
    yRangePossible = (this->height() - 2 * this->imageOffset) / this->scalingK;

    rOffSet = this->imageOffset / this->scalingK;

    //painter.drawLine(0, 0, this->width(), this->height());

    for (unsigned i = 0, len = Canvas::quantityPoints; i < len; i += 2)
    {
        qDebug() << "New Heshok" << Canvas::projectedPoints[i].x << Canvas::projectedPoints[i].y;
        qDebug() << "New Heshok" << Canvas::projectedPoints[i + 1].x << Canvas::projectedPoints[i + 1].y;

        vector2i_t lineBegin = converToRast(Canvas::projectedPoints[i], this->width(), this->height(), this->scalingK);
        vector2i_t lineEnd = converToRast(Canvas::projectedPoints[i + 1], this->width(), this->height(), this->scalingK);

        qDebug() << "POINTS: " << lineBegin.x << lineBegin.y << lineEnd.x << lineEnd.y;

        painter.drawLine(lineBegin.x, lineBegin.y, lineEnd.x, lineEnd.y);
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    //setDisplayRange();
    //setScalingK();
    draw();
}
