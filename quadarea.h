#ifndef QUADAREA_H
#define QUADAREA_H

#include "mesh.h"
#include "function.h"
#include <trianglearea.h>
#include <floor.h>

enum class QGram{
    QQ=75,
    QTT=100
};

class QuadArea
{
public:

    QuadArea();
    QuadArea(Point pa, Point pb, Point pc, Point pd);
    void subdivision(Mesh& m);
    float aire();
    float forme(); // Perimetre / Aire
    QuadArea shrink();
    void addToMesh(Mesh& m);
    void subdivisionPate(Mesh& m);

private:
    Point p[4];
    int longestEdge();
};

#endif // QUADAREA_H
