//
// Created by mbola on 3/24/2025.
//

#ifndef INC_2_RAY_H
#define INC_2_RAY_H


#include "Vector.h"
class Ray{
public:
    Ray();
    Ray(Vector origin, Vector direction);
    Ray(Vector origin, float dis);
    Ray(Vector origin, Vector direction, float dis);

    Vector Origin() const {return Origin_;}
    void Origin(Vector o) {Origin_ = o;}

    Vector Destination() const {return Destination_;}
    void Destination(Vector d) {Destination_ = d;}

    Vector Direction() const {return Direction_;}
    void Direction(Vector d) {Direction_ = d;}

    float Distance() const {return Distance_;}
    void Distance(float d) {Distance_ = d;}


private:
    Vector Origin_;
    Vector Destination_;
    Vector Direction_;
    float Distance_;
};


#endif //INC_2_RAY_H
