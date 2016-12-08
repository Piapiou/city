#ifndef GROUNDFLOOR_H
#define GROUNDFLOOR_H

#include "mesh.h"
#include "point.h"

class GroundFloor
{
public:
    GroundFloor(Point p1, Point p2, Point p3, Point p4, float h);
    void subdivision(Mesh& m);
    void makeMesh(Mesh &m);

private:
    Point p1, p2, p3, p4;
    float size;
};

#endif // GROUNDFLOOR_H
