//
// Created by mbola on 3/25/2025.
//

#ifndef INC_2_QUATERNION_H
#define INC_2_QUATERNION_H

#pragma once
#include "Vector.h"

class Quaternion{
public:
    float s;
    Vector v;
    Quaternion();
    Quaternion(float s, Vector v);
    ~Quaternion();
    Quaternion(const Quaternion &value);
    Quaternion& operator=(const Quaternion &value);
    void operator+=(const Quaternion& q);
    Quaternion operator+(const Quaternion& q);
    void operator-=(const Quaternion& q);
    Quaternion operator-(const Quaternion& q);
    void operator*=(const float value);
    Quaternion operator*(const float value);
    Quaternion operator*(const Quaternion& other) const;
    float norm();
    void normalize();
    void convertToUnitNormQuaternion();
    Quaternion conjugate();
    Quaternion inverse();
};

#endif //INC_2_QUATERNION_H
