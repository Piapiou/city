#ifndef ROOF_H
#define ROOF_H

#include "mesh.h"

class Roof
{
public:
    Roof(Point p1, Point p2, Point p3, Point p4);
    void makeMesh(Mesh& m);

private:
    Point p1, p2, p3, p4;
};

#endif // ROOF_H
