#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mesh.h"
#include "groundfloor.h"
#include <iostream>
#include <time.h>
#include <quadarea.h>
#include <roundfloor.h>

int main(int, char **)
{
    Mesh m = Mesh();
    srand(time(NULL));

    GroundFloor gf = GroundFloor(Point(50.0,-10.0,0.0),
                                 Point(10.0,50.0,0.0),
                                 Point(-50.0,10.0,0.0),
                                 Point(-10.0,-50.0,0.0), 3.0);
    gf.subdivision(m);

    m.toOBJ("C:/Users/toshiba/Desktop/building.obj");

    return 0;
}
