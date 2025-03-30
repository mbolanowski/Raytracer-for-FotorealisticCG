//
// Created by mbola on 3/24/2025.
//

#ifndef INC_2_POINT_H
#define INC_2_POINT_H


#pragma once
#include <string>

class Point{
public:
    float x, y, z;

    Point(float x, float y, float z);
    Point(const Point &p);
    ~Point();

    void Add(const Point &p);
};

#endif //INC_2_POINT_H
