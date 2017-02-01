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
    float nx[n];
    float ny[n];

    for (int i = 0; i < n; i++) {
        nx[i] = - p[(i+1)%n].y() + p[i].y();
        ny[i] = p[(i+1)%n].x() - p[i].x();

        // réajustement de la normal pour qu'elle soit à la taille du décalage
        float n = std::sqrt(std::pow(nx[i],2.0)+std::pow(ny[i],2.0));
        nx[i] = (nx[i]/n)*d;
        ny[i] = (ny[i]/n)*d;
    }

    // Calcul des droites réduite
    float a[n];
    float b[n];

    for (int i = 0; i < n; i++) {
        a[i] = (p[i].y()-p[(i+1)%n].y())/(p[i].x()-p[(i+1)%n].x());
        b[i] = p[i].y()+ny[i]-a[i]*(p[i].x()+nx[i]);
    }
    // Calcul des point d'intersection

    float x[n];
    float y[n];
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
                      (A.y() + (valDp * e1.y()) / len2), 0.0);

    return pp;
}
