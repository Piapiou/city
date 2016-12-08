#include "groundfloor.h"
#include "floor.h"
#include <iostream>

GroundFloor::GroundFloor(Point p1, Point p2, Point p3, Point p4, float h)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    size = h;
}

void GroundFloor::subdivision(Mesh& m) {
    this->makeMesh(m);
    Floor f(Point(p1.x(),p1.y(),p1.z()+size),
            Point(p2.x(),p2.y(),p2.z()+size),
            Point(p3.x(),p3.y(),p3.z()+size),
            Point(p4.x(),p4.y(),p3.z()+size),size);
    f.subdivision(m);
}

void GroundFloor::makeMesh(Mesh& m) {
    m.merge(Mesh::makeFloor(p1,p2,p3,p4,size));
}
