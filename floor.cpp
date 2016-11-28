#include "floor.h"
#include "roof.h"
#include <iostream>

Floor::Floor(Point p1, Point p2, Point p3, Point p4, float h)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    size = h;
}

void Floor::subdivision(Mesh& m) {

    this->makeMesh(m);

    float i = (float)(rand()) / (float)(RAND_MAX);

    if (i < FLOOR_T1) {

        Floor f(Point(p1.x(),p1.y(),p1.z()+size),
                Point(p2.x(),p2.y(),p2.z()+size),
                Point(p3.x(),p3.y(),p3.z()+size),
                Point(p4.x(),p4.y(),p3.z()+size),size);
        f.subdivision(m);

    } else if (i < FLOOR_T2) {

        Floor f(Point(p1.x(),p1.y(),p1.z()+size),
                Point(p2.x(),p2.y(),p2.z()+size),
                Point(p3.x(),p3.y(),p3.z()+size),
                Point(p4.x(),p4.y(),p3.z()+size),size);
        f.shrink(2.0);
        f.subdivision(m);

    } else {

        Roof r(Point(p1.x(),p1.y(),p1.z()+size),
               Point(p2.x(),p2.y(),p2.z()+size),
               Point(p3.x(),p3.y(),p3.z()+size),
               Point(p4.x(),p4.y(),p3.z()+size));
        r.makeMesh(m);

    }
}

void Floor::shrink(float d) {

}

void Floor::makeMesh(Mesh& m) {
    m.merge(Mesh::makeFloor(p1,p2,p3,p4,size));
}


