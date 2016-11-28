#ifndef TRIANGLEAREA_H
#define TRIANGLEAREA_H

#include "mesh.h"

enum class TGram{
    TTT=50,
    QT=100
};

class TriangleArea
{
public:
    TriangleArea();
    void subdivision(Mesh& m);
    float aire();
    float forme(); // triangle inscrit / cercle circonscrit
    TriangleArea shrink();
};

#endif // TRIANGLEAREA_H
