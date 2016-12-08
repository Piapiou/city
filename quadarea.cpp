#include "quadarea.h"

QuadArea::QuadArea()
{
    srand(time(NULL));
}

QuadArea::QuadArea(Point pa, Point pb, Point pc, Point pd)
{
    this->p[0]=pa;
    this->p[1]=pb;
    this->p[2]=pc;
    this->p[3]=pd;

    srand(time(NULL));
}

void QuadArea::subdivision(Mesh& m)
{
    int seuil=100;

    if (computeQuadArea(p) < seuil){
        printf("%f",this->p[0].x());
        return;
    }

    //int alea=rand()%100;
    int alea=1;
    if(alea<=(int)QGram::QQ){
        Point m1=randomMid(p[longestEdge()],p[(longestEdge()+2)%4]);
        Point m2=randomMid(p[(longestEdge()+1)%4],p[(longestEdge()+3)%4]);
        QuadArea q1= QuadArea(p[longestEdge()],m1,m2,p[(longestEdge()+2)%4]);
        QuadArea q2= QuadArea(m1,p[(longestEdge()+1)%4],p[(longestEdge()+2)%4],m2);
        q1.subdivision(m);
        q2.subdivision(m);
    }
    else if(alea<=(int)QGram::QTT){

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



























