#include "trianglearea.h"

TriangleArea::TriangleArea()
{

}

TriangleArea::TriangleArea(Point pa, Point pb, Point pc){
    this->p[0]=pa;
    this->p[1]=pb;
    this->p[2]=pc;
}

void TriangleArea::subdivision(Mesh& m){
    int seuil=1600;
    float t=computeTriangleArea(p[0],p[1],p[2]);
    if (computeTriangleArea(p[0],p[1],p[2]) < seuil){

        return;
    }

    int alea=rand()%100;
    if(alea<=(int)TGram::QT){
        Point m1=randomMid(p[alea%3],p[alea%3+1]);
        Point m2=randomMid(p[alea%3],p[alea%3+2]);

        TriangleArea t1=TriangleArea(p[alea%3],m1,m2);
        QuadArea q1=QuadArea(m1,p[alea%3+1],p[alea%3+2],m2);

        t1.subdivision(m);
        q1.subdivision(m);
    }
    else if(alea<=(int)TGram::TTT){
        Point m1=randomMid(p[0],p[1]);
        Point m2=randomMid(p[1],p[2]);
        Point m3=randomMid(p[2],p[0]);

        TriangleArea t1=TriangleArea(p[0],m1,m3);
        TriangleArea t2=TriangleArea(p[1],m1,m2);
        TriangleArea t3=TriangleArea(p[2],m2,m3);

        t1.subdivision(m);
        t2.subdivision(m);
        t3.subdivision(m);
    }
}
