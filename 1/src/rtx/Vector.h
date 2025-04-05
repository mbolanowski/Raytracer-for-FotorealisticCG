#ifndef INC_2_VECTOR_H
#define INC_2_VECTOR_H

#define M_PI 3.14159265358979323846

#pragma once
#include <iostream>
#include "Point.h"


class Vector{
public:
    float x, y ,z;

    Vector() noexcept;
    Vector(const Vector& v);
    Vector(Point p1, Point p2);
    Vector(float x, float y, float z);
    ~Vector();

    void Add(const Vector &v);
    Vector AddV(Vector v);
    void Sub(const Vector &v);
    Vector SubV(Vector v);
    void Div(float f);
    Vector DivV(float f);
    void Mag(float f);
    Vector MagV(float f) const;
    float Length() const;
    void Normalize();
    Vector NormalizeV();
    Vector Dot(Vector v);
    float DotProduct(Vector v) const;
    Vector Cross(Vector v) const;

    float AngleBetween(Vector v);

    Vector rotateVectorAboutAngleAndAxis(float uAngle, Vector &uAxis);

    Vector operator-() const;
    Vector operator+(const Vector &v) const;
    Vector operator-(const Vector &v) const;
    Vector operator*(float f) const;
    bool operator==(const Vector &v) const;
    bool operator<(const Vector &v) const;
    bool operator>(const Vector &v) const;
};

#endif //INC_2_VECTOR_H
