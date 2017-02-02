#ifndef TRIANGLEAREA_H
#define TRIANGLEAREA_H

#include "mesh.h"
#include "function.h"

enum class TGram{
    QTT=50,
    QT=100
};

class TriangleArea
{
public:
    TriangleArea();
    TriangleArea(Point pa, Point pb, Point pc);
    void subdivision(Mesh& m,QImage& img,float shrinkSize);
    TriangleArea shrink();
    void subdivisionPate(Mesh& m);
    Point p[3];
    float aire;

};

#endif // TRIANGLEAREA_H
