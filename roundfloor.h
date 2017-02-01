#ifndef ROUNDFLOOR_H
#define ROUNDFLOOR_H

#include "point.h"
#include "mesh.h"

class RoundFloor
{
public:
    RoundFloor(Point c, float r, float size);
    void subdivision(Mesh& m);
    void makeMesh(Mesh &m);
    void shrink(float d);

    static constexpr float FLOOR_T1 = 0.85;
    static constexpr float FLOOR_T2 = 0.99;
    static constexpr float FLOOR_T3 = 1.00;

private:
    Point c;
    float r;
    float size;
};

#endif // ROUNDFLOOR_H
