#include "Point.h"

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}
Point::Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}
Point::~Point() noexcept {}

void Point::Add(const Point &p) {
    x += p.x;
    y += p.y;
    z += p.z;
}

