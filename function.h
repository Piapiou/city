#ifndef FUNCTION_H
#define FUNCTION_H

#include "point.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "quadarea.h"
#include <QImage>
#include <QPainter>
#include <QPoint>

Point randomMid(Point p1, Point p2);
float computeQuadArea(Point a,Point b,Point c,Point d);
float computeTriangleArea(Point a,Point b,Point c);
float distanceTwoPoints(Point p1, Point p2);
void shrinkN(Point * p, int n, float d);
Point getProjectedPointOnLine(Point, Point, Point);

bool polyTooSmall(Point* points, int nbPoint, float sizeMini);

//To draw image
void drawPoly(Point* points, int nbPoint, QImage& img);

#endif // FUNCTION_H
