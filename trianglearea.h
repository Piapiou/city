#ifndef TRIANGLEAREA_H
#define TRIANGLEAREA_H

#include "mesh.h"
#include "function.h"

enum class TGram{
    TTT=50,
    QT=100
};

class TriangleArea
{
public:
    TriangleArea();
    TriangleArea(Point pa, Point pb, Point pc);
    void subdivision(Mesh& m);
    float aire();
    float forme(); // triangle inscrit / cercle circonscrit
    TriangleArea shrink();
private:
    Point p[3];

};

#endif // TRIANGLEAREA_H
