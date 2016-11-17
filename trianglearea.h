#ifndef TRIANGLEAREA_H
#define TRIANGLEAREA_H

#include "mesh.h"

class TriangleArea
{
public:
    TriangleArea();
    void subdivision(Mesh& m);
    float aire();
    float forme(); // triangle inscrit / cercle circonscrit
    TriangleArea shrink();
};

#endif // TRIANGLEAREA_H
