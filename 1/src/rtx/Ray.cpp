#include "Ray.h"

Ray::Ray() : Origin_(Vector(0, 0, 0)), Direction_(Vector(0, 0, 0)), Distance_(0) {}
Ray::Ray(Vector origin, Vector direction) : Origin_(origin), Direction_(direction), Distance_(0) {}
Ray::Ray(Vector origin, float dis) : Origin_(origin), Direction_(Vector(0, 0, 0)), Distance_(dis) {}
Ray::Ray(Vector origin, Vector direction, float dis) : Origin_(origin), Direction_(direction), Distance_(dis) {}