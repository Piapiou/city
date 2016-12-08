#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <mesh.h>
#include <quadarea.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    srand(time(NULL));
    Mesh m=Mesh();
    QuadArea q=QuadArea(Point(0,0,0),Point(1000,0,0),Point(1000,1000,0),Point(0,1000,0));
    q.subdivision(m);
    m.toOBJ("test.obj");
    return app.exec();
}
