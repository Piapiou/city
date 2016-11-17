#ifndef QUADAREA_H
#define QUADAREA_H

#include "mesh.h"

class QuadArea
{
public:
    QuadArea();
    void subdivision(Mesh& m);
    float aire();
    float forme(); // Perimetre / Aire
    QuadArea shrink();

private:
    Point pa, pb, pc, pd;
};

#endif // QUADAREA_H
