#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mesh.h"
#include "groundfloor.h"
#include <iostream>
#include <time.h>

int main(int, char **)
{
    Mesh m = Mesh();
    srand(time(NULL));

//    GroundFloor gf = GroundFloor(Point(50.0,-10.0,0.0),
//                                 Point(10.0,50.0,0.0),
//                                 Point(-50.0,10.0,0.0),
//                                 Point(-10.0,-50.0,0.0), 3.0);
    GroundFloor gf = GroundFloor(Point(50.0,25.0,0.0),
                                 Point(50.0,40.0,0.0),
                                 Point(0.0,50.0,0.0),
                                 Point(0.0,0.0,0.0), 3.0);

    std::cout << "Building generation\n" << std::flush;
    gf.subdivision(m);
    std::cout << "Building created\n" << std::flush;

    m.toOBJ("C:/Users/toshiba/Desktop/building.obj");

    return 0;
}
