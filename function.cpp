#include "function.h"
#include <iostream>

/**
 * @brief Calcul un point proche du milieu des deux point en paramètre.
 * @param p1
 * @param p2
 * @return
 */
Point randomMid(Point p1, Point p2) {
    float pond1=((float)((rand()%10)+5)/20);
    float pond2=1-pond1;

    return Point(QVector3D((p1.x()*pond1)+(p2.x()*pond2),(p1.y()*pond1)+(p2.y()*pond2),(p1.z()*pond1)+(p2.z()*pond2)));
}

float computeQuadArea(Point a,Point b,Point c,Point d){
    return computeTriangleArea(a,b,c)+computeTriangleArea(c,d,a);
}

float computeTriangleArea(Point a,Point b,Point c){
    float ab=distanceTwoPoints(a,b);
    float bc=distanceTwoPoints(b,c);
    float ca=distanceTwoPoints(c,a);
    float p=(ab+bc+ca)/2;
    return(sqrt(p*(p-ab)*(p-bc)*(p-ca)));
}

float distanceTwoPoints(Point p1, Point p2){
    return sqrt((p2.x()-p1.x())*(p2.x()-p1.x())+(p2.y()-p1.y())*(p2.y()-p1.y()));
}

void shrinkN(Point * p, int n, float d) {

    // Calcul des normales des 4 cotés
    double nx[n];
    double ny[n];

    for (int i = 0; i < n; i++) {
        nx[i] = - (double)p[(i+1)%n].y() + (double)p[i].y();
        ny[i] = (double)p[(i+1)%n].x() - (double)p[i].x();

        // réajustement de la normal pour qu'elle soit à la taille du décalage
        double n = std::sqrt(std::pow(nx[i],2.0)+std::pow(ny[i],2.0));
        nx[i] = (nx[i]/n)*(double)d;
        ny[i] = (ny[i]/n)*(double)d;
    }

    // Calcul des droites réduite
    double a[n];
    double b[n];

    for (int i = 0; i < n; i++) {
        a[i] = (p[i].y()-p[(i+1)%n].y())/(p[i].x()-p[(i+1)%n].x());
        b[i] = p[i].y()+ny[i]-a[i]*(p[i].x()+nx[i]);
    }
    // Calcul des point d'intersection

    double x[n];
    double y[n];
    for (int i = 0; i < n; i++) {
        if (a[i] == 1.0/0.0 || a[i] == -1.0/0.0) {
            x[i] = p[i].x()+nx[i];
            y[i] = a[(i+1)%n]*x[i]+b[(i+1)%n];
        } else if (a[(i+1)%n] == 1.0/0.0 || a[(i+1)%n] == -1.0/0.0) {
            x[i] =p[(i+1)%n].x()+nx[(i+1)%n];
            y[i] = a[i]*x[i]+b[i];
        } else {
            x[i] = (b[i]-b[(i+1)%n])/(a[(i+1)%n]-a[i]);
            y[i] = a[i]*x[i]+b[i];
        }

    }

    for (int i = 0; i < n; i++) {
        p[i].setX(x[(i+n-1)%n]);
        p[i].setY(y[(i+n-1)%n]);
    }
}

Point getProjectedPointOnLine(Point A, Point B, Point C)
{
    // get dot product of e1, e2
    Point e1 = Point(B.x() - A.x(), B.y() - A.y(), 0.0);
    Point e2 = Point(C.x() - A.x(), C.y() - A.y(), 0.0);
    double valDp = QVector3D::dotProduct(e1, e2);

    // get squared length of e1
    double len2 = e1.x() * e1.x() + e1.y() * e1.y();

    Point pp = Point((A.x() + (valDp * e1.x()) / len2),
                      (A.y() + (valDp * e1.y()) / len2), 0.2);

    return pp;
}

void drawTriangle(Point * p, QImage& img){

    QPainter qPainter(&img);
    //qPainter.setBrush(Qt::NoBrush);

    qPainter.setPen(Qt::red);
    QPainterPath path;
    QVector<QPointF> pf;

    pf.push_back(QPointF(p[0].x(),p[0].y()));
    pf.push_back(QPointF(p[1].x(),p[1].y()));
    pf.push_back(QPointF(p[2].x(),p[2].y()));
    pf.push_back(QPointF(p[3].x(),p[3].y()));

    path.addPolygon(QPolygonF(pf));
    qPainter.fillPath(path, Qt::red);
    qPainter.drawPath(path);

}

void drawPoly(Point* points, int nbPoint, QImage& img){
    QPainter qPainter(&img);
    //qPainter.setBrush(Qt::NoBrush);
    QPainterPath path;
    QVector<QPointF> pf;

    for(int i=0;i<nbPoint;i++){
        pf.push_back(QPointF(points[i].x(),points[i].y()));
    }
    path.addPolygon(QPolygonF(pf));

    qPainter.setPen(QPen(Qt::black, 2));
    qPainter.fillPath(path, Qt::red);
    qPainter.drawPath(path);

}

bool polyTooSmall(Point* points,int nbPoint, float sizeMini){
    for(int i=0;i<nbPoint-1;i++){
        if(distanceTwoPoints(points[i],points[i+1])<sizeMini){
             return true;
        }
    }
    return false;
}
