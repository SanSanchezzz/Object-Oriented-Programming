#ifndef CANVAS_H
#define CANVAS_H

#include <QPainter>
#include <QPointF>
#include <QWidget>
#include <QColor>
#include <QList>

#include "math.h"
#include "graphics.h"

namespace MyColors
{
    const QColor gBackground = QColor("#eeeeee");
    const QColor red = QColor("#d50000");
    const QColor green = QColor("#00bc6c");
    const QColor blue = QColor("#2962ff");
    const QColor black = QColor("#000000");
    const QColor pink = QColor("#e91e63");
}

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void getPoints(vector4d_t *pP, unsigned qP);

    void setDisplayRange();

    void setScalingK();

signals:

public slots:

private:
    double xMax, xMin;
    double yMin, yMax;
    double xRange, yRange;
    double imageOffset;
    double scalingK;
    QColor BGColor = MyColors::gBackground;
    QColor LineColor = MyColors::black;
    vector4d_t *projectedPoints = nullptr;
    unsigned int quantityPoints = 0;

    void draw();

    double xCartToDisp(double xC);
    double yCartToDisp(double yC);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
