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

void QuadArea::subdivisionPate(Mesh& m)
{
    // Shrink trottoir, longueur 2m, hauteur 0.2m
    Point p2[4];
    for(int i = 0; i < 4; i++)
    {
        p2[i] = this->p[i];
    }
    shrinkN(p2, 4, 2.0);

    m.merge(Mesh::makeRoof(p2[0], p2[1], p2[2], p2[3]));
    m.merge(Mesh::makeRoof(p2[0], p2[1], this->p[1], this->p[0]));
    m.merge(Mesh::makeRoof(p2[1], p2[2], this->p[2], this->p[1]));
    m.merge(Mesh::makeRoof(p2[2], p2[3], this->p[3], this->p[2]));
    m.merge(Mesh::makeRoof(p2[3], p2[0], this->p[0], this->p[3]));

    Point p3[4];
    for(int i = 0; i < 4; i++)
    {
        p3[i] = p2[i];
    }

    p3[0].setZ(p2[0].z() + 0.2);
    p3[1].setZ(p2[1].z() + 0.2);
    p3[2].setZ(p2[2].z() + 0.2);
    p3[3].setZ(p2[3].z() + 0.2);

    m.merge(Mesh::makeRoof(p2[0], p2[1], p3[1], p3[0]));
    m.merge(Mesh::makeRoof(p2[1], p2[2], p3[2], p3[1]));
    m.merge(Mesh::makeRoof(p2[2], p2[3], p3[3], p3[2]));
    m.merge(Mesh::makeRoof(p2[3], p2[0], p3[0], p3[3]));

    m.merge(Mesh::makeRoof(p3[0], p3[1], p3[2], p3[3]));

    for(int i = 0; i < 4; i++)
    {
        p2[i] = p3[i];
    }

    shrinkN(p3, 4, 25);

    // Projetés ortho
    Point pOrtho[8];
    pOrtho[0] = getProjectedPointOnLine(p2[0], p2[1], p3[0]);
    pOrtho[1] = getProjectedPointOnLine(p2[0], p2[1], p3[1]);
    pOrtho[2] = getProjectedPointOnLine(p2[1], p2[2], p3[1]);
    pOrtho[3] = getProjectedPointOnLine(p2[1], p2[2], p3[2]);
    pOrtho[4] = getProjectedPointOnLine(p2[2], p2[3], p3[2]);
    pOrtho[5] = getProjectedPointOnLine(p2[2], p2[3], p3[3]);
    pOrtho[6] = getProjectedPointOnLine(p2[3], p2[0], p3[3]);
    pOrtho[7] = getProjectedPointOnLine(p2[3], p2[0], p3[0]);

    // Coins
    Floor coins[4];

    coins[0] = Floor(p2[0], pOrtho[0], p3[0], pOrtho[7], 3);
    coins[1] = Floor(p2[1], pOrtho[2], p3[1], pOrtho[1], 3);
    coins[2] = Floor(p2[2], pOrtho[4], p3[2], pOrtho[3], 3);
    coins[3] = Floor(p2[3], pOrtho[6], p3[3], pOrtho[5], 3);

    for(int i = 0; i < 4; i++)
    {
        coins[i].subdivision(m);
    }

    // Inter-Coins
    int alea = rand() % 100;

    if(alea < 50)
    {
        Floor coin;

        for(int i = 0; i < 4; i++)
        {
            Point mid = (p3[i] + p3[(i + 1) % 4]) / 2;
            Point mid2 = (pOrtho[i * 2] + pOrtho[i * 2 + 1]) / 2;

            coin = Floor(p3[i], pOrtho[i * 2], mid2, mid, 3);
            coin.subdivision(m);

            coin = Floor(mid2, pOrtho[i * 2 + 1], p3[(i + 1) % 4], mid, 3);
            coin.subdivision(m);
        }
    }
    else
    {
        Floor coin;

        for(int i = 0; i < 4; i++)
        {
            Point mid = (p3[i] + p3[(i + 1) % 4]) / 2;
            Point mid2 = (pOrtho[i * 2] + pOrtho[i * 2 + 1]) / 2;

            coin = Floor(p3[i], pOrtho[i * 2], mid2, mid, 3);
            coin.subdivision(m);

            coin = Floor(mid2, pOrtho[i * 2 + 1], p3[(i + 1) % 4], mid, 3);
            coin.subdivision(m);
        }
    }
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
