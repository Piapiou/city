#ifndef FLOOR_H
#define FLOOR_H

#include "mesh.h"

class Floor
{
public:
    Floor(Point p1, Point p2, Point p3, Point p4, float h);
    void subdivision(Mesh& m);
    void makeMesh(Mesh& m);
    void shrink(float d);

    static constexpr float FLOOR_T1 = 0.65;
    static constexpr float FLOOR_T2 = 0.90;
    static constexpr float FLOOR_T3 = 1.00;

private:

    Point p1, p2, p3, p4;
    float size;
};

#endif // FLOOR_H
