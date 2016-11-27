#include "function.h"
/**
 * @brief Calcul un point proche du milieu des deux point en paramètre.
 * @param p1
 * @param p2
 * @return
 */
Point randomMid(Point p1, Point p2) {

    srand(time(NULL));

    float pond1=((rand()%10)+5)/10;
    float pond2=1.5-pond1;

    return Point(QVector3D((p1.x()*pond1)+(p2.x()*pond2)/2,(p1.y()*pond1)+(p2.y()*pond2)/2,(p1.z()*pond1)+(p2.z()*pond2)/2));
}

float computeQuadArea(Point* p){
    return 0;
}

float distanceTwoPoints(Point p1, Point p2){

    return sqrt((p2.x()-p1.x())*(p2.x()-p1.x())+(p2.y()-p1.y())*(p2.y()-p1.y()));

}
