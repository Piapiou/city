#ifndef QUADAREA_H
#define QUADAREA_H

#include "mesh.h"
#include "function.h"
#include <trianglearea.h>
#include <floor.h>
#include <roundfloor.h>

enum class QGram{
    QQ=75,
    QTT=100
};

class QuadArea
{
public:

    QuadArea();
    QuadArea(Point pa, Point pb, Point pc, Point pd);
    void subdivision(Mesh& m,QImage& img,float shrinkSize);
    QuadArea shrink();
    void addToMesh(Mesh& m);
    Point getPoint(int ind);
    void subdivisionPate(Mesh& m);
    Point p[4];
    float aire;

private:


    int longestEdge();
};

#endif // QUADAREA_H
