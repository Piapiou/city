#include "trianglearea.h"

TriangleArea::TriangleArea()
{

}

TriangleArea::TriangleArea(Point pa, Point pb, Point pc){
    this->p[0]=pa;
    this->p[1]=pb;
    this->p[2]=pc;
    aire=computeTriangleArea(pa,pb,pc);
}

void TriangleArea::subdivision(Mesh& m,QImage& img,float shrinkSize){
    int seuil=3000;

    shrinkSize=shrinkSize/2>2?shrinkSize/2:2;

    aire=computeTriangleArea(p[0],p[1],p[2]);
    if (aire < seuil){
        drawPoly(p,3,img);
        return;
    }

    int alea=rand()%100;

    if(alea<=(int)TGram::QT){
        Point m1=randomMid(p[alea%3],p[(alea+1)%3]);
        Point m2=randomMid(p[alea%3],p[(alea+2)%3]);

        TriangleArea t1=TriangleArea(p[alea%3],m1,m2);
        QuadArea q1=QuadArea(m1,p[(alea+1)%3],p[(alea+2)%3],m2);

        if(!polyTooSmall(t1.p,3,shrinkSize)){
                        shrinkN(t1.p,3,shrinkSize);
            t1.subdivision(m,img,shrinkSize);

        }
        if(!polyTooSmall(q1.p,4,shrinkSize)){
                        shrinkN(q1.p,4,shrinkSize);
            q1.subdivision(m,img,shrinkSize);

        }
    }
    else if(alea<=(int)TGram::QTT){
        Point m1=randomMid(p[0],p[1]);
        Point m2=randomMid(p[1],p[2]);
        Point m3=randomMid(p[2],p[0]);

        TriangleArea t1=TriangleArea(p[0],m1,m3);
        TriangleArea t2=TriangleArea(p[1],m1,m2);
        QuadArea q1=QuadArea(m1,m2,m3,p[2]);

        if(!polyTooSmall(t1.p,3,shrinkSize)){
            shrinkN(t1.p,3,shrinkSize);
            t1.subdivision(m,img,shrinkSize);
        }
        if(!polyTooSmall(t2.p,3,shrinkSize)){
            shrinkN(t2.p,3,shrinkSize);
            t2.subdivision(m,img,shrinkSize);
        }
        if(!polyTooSmall(q1.p,4,shrinkSize)){
            shrinkN(q1.p,4,shrinkSize);
            q1.subdivision(m,img,shrinkSize);
        }
    }
}

void TriangleArea::subdivisionPate(Mesh& m)
{

}
