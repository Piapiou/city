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
    int seuil=15000;

    shrinkSize=shrinkSize/2>2?shrinkSize/2:2;

    aire=computeTriangleArea(p[0],p[1],p[2]);
    if (aire < seuil){
        subdivisionPate(m);
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
    // Shrink trottoir, longueur 2m, hauteur 0.2m
    Point p2[3];
    for(int i = 0; i < 3; i++)
    {
        p2[i] = this->p[i];
    }
    shrinkN(p2, 3, 2.0);

    m.merge(Mesh::makeTriangle(p2[0], p2[1], p2[2]));
    m.merge(Mesh::makeRoof(p2[0], p2[1], this->p[1], this->p[0]));
    m.merge(Mesh::makeRoof(p2[1], p2[2], this->p[2], this->p[1]));
    m.merge(Mesh::makeRoof(p2[2], p2[0], this->p[0], this->p[2]));

    Point p3[4];
    for(int i = 0; i < 3; i++)
    {
        p3[i] = p2[i];
    }

    p3[0].setZ(p2[0].z() + 0.2);
    p3[1].setZ(p2[1].z() + 0.2);
    p3[2].setZ(p2[2].z() + 0.2);
    p3[3].setZ(p2[3].z() + 0.2);

    m.merge(Mesh::makeRoof(p2[0], p2[1], p3[1], p3[0]));
    m.merge(Mesh::makeRoof(p2[1], p2[2], p3[2], p3[1]));
    m.merge(Mesh::makeRoof(p2[2], p2[0], p3[0], p3[2]));

    m.merge(Mesh::makeTriangle(p3[0], p3[1], p3[2]));

    if(this->aire < 3500)
    {
        RoundFloor round = RoundFloor((p3[0] + p3[1] + p3[2]) / 3, 10, 5);
        round.subdivision(m);
    }
    else
    {
        for(int i = 0; i < 3; i++)
        {
            p2[i] = p3[i];
        }

        shrinkN(p3, 3, 14);
        shrinkN(p2, 3, 0.5);

        // Projetés ortho
        Point pOrtho[6];
        pOrtho[0] = getProjectedPointOnLine(p2[0], p2[1], p3[0]);
        pOrtho[1] = getProjectedPointOnLine(p2[0], p2[1], p3[1]);
        pOrtho[2] = getProjectedPointOnLine(p2[1], p2[2], p3[1]);
        pOrtho[3] = getProjectedPointOnLine(p2[1], p2[2], p3[2]);
        pOrtho[4] = getProjectedPointOnLine(p2[2], p2[0], p3[2]);
        pOrtho[5] = getProjectedPointOnLine(p2[2], p2[0], p3[0]);

        // Coins
        Floor coins[3];

        coins[0] = Floor(p2[0], pOrtho[0], p3[0], pOrtho[5], 3, rand() % 15 + 25);
        coins[1] = Floor(p2[1], pOrtho[2], p3[1], pOrtho[1], 3, rand() % 15 + 25);
        coins[2] = Floor(p2[2], pOrtho[4], p3[2], pOrtho[3], 3, rand() % 15 + 25);

        for(int i = 0; i < 3; i++)
        {
            coins[i].subdivision(m);
        }

        // Inter-Coins
        Floor coin;


        for(int i = 0; i < 3; i++)
        {
            Point mid = (p3[i] + p3[(i + 1) % 3]) / 2;
            Point mid2 = (pOrtho[i * 2] + pOrtho[i * 2 + 1]) / 2;

            coin = Floor(p3[i], pOrtho[i * 2], mid2, mid, 3, rand() % 15 + 20);
            coin.subdivision(m);

            coin = Floor(mid2, pOrtho[i * 2 + 1], p3[(i + 1) % 3], mid, 3, rand() % 15 + 20);
            coin.subdivision(m);
        }
    }
}
