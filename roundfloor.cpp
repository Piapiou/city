#include "roundfloor.h"
#include "mesh.h"

RoundFloor::RoundFloor(Point c, float r, float size)
{
    this->c = c;
    this->r = r;
    this->size = size;
}

void RoundFloor::subdivision(Mesh& m) {

    this->makeMesh(m);
    float i = (float)rand() / (float)RAND_MAX;


    if (i < FLOOR_T1) {

        RoundFloor f(Point(c.x(),c.y(),c.z()+size),r,size);

        f.subdivision(m);

    } else if (i < FLOOR_T2 && 2.0 < r) {

        RoundFloor f(Point(c.x(),c.y(),c.z()+size),r,size);
        f.shrink(2.0);
        f.subdivision(m);

    } else {

    }

}



void RoundFloor::shrink(float d) {
    r = r-d;
}

void RoundFloor::makeMesh(Mesh& m) {
    m.merge(Mesh::makeCylinder(c,size*0.95,r,20));
    m.merge(Mesh::makeCylinder(Point(c.x(),c.y(),c.z()+size*0.95),size*0.05,r-0.3,20));
}

