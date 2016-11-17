#ifndef LINE_H
#define LINE_H
#include <point.h>

class Line
{
public:
    Line();
    Point intersection(Line d);
    Line shift(float d);

private:
    Point p1, p2;
};

#endif // LINE_H
