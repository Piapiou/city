#include "roof.h"

Roof::Roof(Point p1, Point p2, Point p3, Point p4)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

void Roof::makeMesh(Mesh& m) {

    m.merge(Mesh::makeRoof(p1,p2,p3,p4));

}
