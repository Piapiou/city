#include "quadarea.h"

QuadArea::QuadArea()
{

}

QuadArea::QuadArea(Point pa, Point pb, Point pc, Point pd)
{
    this->p[0]=pa;
    this->p[1]=pb;
    this->p[2]=pc;
    this->p[3]=pd;
}

void QuadArea::subdivision(Mesh& m)
{
    int seuil=1600;
    aire=computeQuadArea(p[0],p[1],p[2],p[3]);
    if (aire< seuil){
        Floor f=Floor(p[0],p[1],p[2],p[3],3);
        f.subdivision(m);
        return;
    }

    int alea=rand()%100;
    if(alea<=(int)QGram::QQ){
        Point m1=randomMid(p[longestEdge()],p[(longestEdge()+1)%4]);
        Point m2=randomMid(p[(longestEdge()+2)%4],p[(longestEdge()+3)%4]);
        QuadArea q1= QuadArea(p[longestEdge()],m1,m2,p[(longestEdge()+3)%4]);
        QuadArea q2= QuadArea(m1,p[(longestEdge()+1)%4],p[(longestEdge()+2)%4],m2);
        q1.subdivision(m);
        q2.subdivision(m);
    }
    else if(alea<=(int)QGram::QTT){

        Point m1=randomMid(p[longestEdge()],p[(longestEdge()+1)%4]);
        Point m2=randomMid(p[(longestEdge()+2)%4],p[(longestEdge()+3)%4]);

        QuadArea q1= QuadArea(p[longestEdge()],m1,m2,p[(longestEdge()+3)%4]);
        QuadArea q2= QuadArea(m1,p[(longestEdge()+1)%4],p[(longestEdge()+2)%4],m2);

        TriangleArea t1=TriangleArea(q2.getPoint(0),q2.getPoint(1),q2.getPoint(2));
        TriangleArea t2=TriangleArea(q2.getPoint(2),q2.getPoint(3),q2.getPoint(0));

        q1.subdivision(m);
        t1.subdivision(m);
        t2.subdivision(m);
    }
}

void QuadArea::addToMesh(Mesh& m){
}

int QuadArea::longestEdge(){
    float max=-1;
    int ind=-1;

    for(int i=0;i<4;i++){
        float first=distanceTwoPoints(p[i],p[(i+1)%4]);
        if(first>max){
            max=first;
            ind=i;
        }
    }

    return ind;
}

Point QuadArea::getPoint(int ind){
    return p[ind];
}

























