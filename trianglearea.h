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
    void subdivision(Mesh& m);
    TriangleArea shrink();
private:
    float aire;
    Point p[3];

};

#endif // TRIANGLEAREA_H
