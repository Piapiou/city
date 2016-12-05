#include "floor.h"
#include "roof.h"
#include <iostream>
#include "function.h"

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

    } else if (i < FLOOR_T2 &&
               !(distanceTwoPoints(p1, p2) < 2.0
                || distanceTwoPoints(p2, p3) < 2.0
                || distanceTwoPoints(p3, p4) < 2.0
                || distanceTwoPoints(p4, p1) < 2.0)) {

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
    Point p[4];
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;

    shrinkN(p,4,d);

    p1 = p[0];
    p2 = p[1];
    p3 = p[2];
    p4 = p[3];
}

void Floor::makeMesh(Mesh& m) {
    m.merge(Mesh::makeFloor(p1,p2,p3,p4,size));
}


