#ifndef QUAD_H
#define QUAD_H


class Quad
{
public:
    Quad();
    Quad(int p1, int p2, int p3, int p4);
    void Quad::getPoint(int i);
private:
    int p[4];
};

#endif // QUAD_H
