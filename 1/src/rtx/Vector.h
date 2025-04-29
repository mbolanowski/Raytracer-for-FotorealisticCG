#ifndef INC_2_VECTOR_H
#define INC_2_VECTOR_H

#define M_PI 3.14159265358979323846

#pragma once
#include <iostream>
#include "Point.h"
#include "../tga/color.h"


class Vector{
public:
    union {
        struct { float x, y, z; };
        struct { float u, v, w; };
        struct { float r, g, b; };
    };

    Vector() noexcept;
    Vector(const Vector& v);
    Vector(Point p1, Point p2);
    Vector(float x, float y, float z);
    Vector(color::color_t from_color) : x(from_color.r), y(from_color.g), z(from_color.b) {}
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

    float AngleBetween(Vector v) const;

    Vector rotateVectorAboutAngleAndAxis(float uAngle, Vector &uAxis);

    Vector reflect(Vector normal) const;
    Vector refract(Vector normal, float indexThis, float indexOther) const;

    inline color::color_t to_color() const { return {x, y, z, 1.0f}; }

    Vector operator-() const;
    Vector operator+(const Vector &v) const;
    Vector operator-(const Vector &v) const;
    Vector operator*(float f) const;
    bool operator==(const Vector &v) const;
    bool operator<(const Vector &v) const;
    bool operator>(const Vector &v) const;
};

template<>
struct std::hash<Vector>
{
    std::size_t operator()(const Vector& s) const noexcept
    {
        std::size_t h1 = std::hash<float>{}(s.x);
        std::size_t h2 = std::hash<float>{}(s.y);
        std::size_t h3 = std::hash<float>{}(s.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2); // or use boost::hash_combine
    }
};

#endif //INC_2_VECTOR_H
