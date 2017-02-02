#include "roof.h"
#include "function.h"

Roof::Roof(Point p1, Point p2, Point p3, Point p4)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

void Roof::makeMesh(Mesh& m) {

    if (!(distanceTwoPoints(p1, p2) < 2
          || distanceTwoPoints(p2, p3) < 2
          || distanceTwoPoints(p3, p4) < 2
          || distanceTwoPoints(p4, p1) < 2
          || distanceTwoPoints(p1, p3) < 2
          || distanceTwoPoints(p2, p4) < 2)) {
        Point p[4];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        p[3] = p4;

        shrinkN(p,4,1);

        p1 = p[0];
        p2 = p[1];
        p3 = p[2];
        p4 = p[3];
    }
    m.merge(Mesh::makeFloor(p1,p2,p3,p4, 3));

}
