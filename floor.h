#ifndef FLOOR_H
#define FLOOR_H

#include "mesh.h"

class Floor
{
public:
    Floor(Point p1, Point p2, Point p3, Point p4, float h);
    Floor(Point p1, Point p2, Point p3, Point p4, float h, int t);
    void subdivision(Mesh& m);
    void makeMesh(Mesh& m);
    void shrink(float d);

    static constexpr int BAT_T1 = 0;
    static constexpr int BAT_T2 = 1;
    static constexpr int BAT_T3 = 2;

    static constexpr float FLOOR_T1 = 0.50;
    static constexpr float FLOOR_T2 = 0.90;
    static constexpr float FLOOR_T3 = 1.00;

private:

    Point p1, p2, p3, p4;
    int type;
    float size;
};

#endif // FLOOR_H
