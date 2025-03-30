#include "Quaternion.h"

constexpr float kDegToRad = 3.14159265358979323846f / 180.0f;

inline float DegreesToRad(float degrees) {
    return degrees * kDegToRad;
}

Quaternion::Quaternion(float s, Vector v) : s(s), v(v) {}
Quaternion::~Quaternion(){}

Quaternion::Quaternion(const Quaternion &value) {
    s=value.s;
    v=value.v;
};

Quaternion& Quaternion::operator=(const Quaternion &value) {
    s=value.s;
    v=value.v;

    return *this;
}

void Quaternion::operator+=(const Quaternion& q){
    s+=q.s;
    v.Add(q.v);
}

Quaternion Quaternion::operator+(const Quaternion& q){
    float scalar = s+q.s;
    Vector imaginary = v.AddV(q.v);

    return Quaternion(scalar, imaginary);
}

void Quaternion::operator-=(const Quaternion& q){
    s-=q.s;
    v.Sub(q.v);
}

Quaternion Quaternion::operator-(const Quaternion& q){
    float scalar = s-q.s;
    Vector imaginary = v.SubV(q.v);
    return Quaternion(scalar, imaginary);
}

void Quaternion::operator*=(const float value){
    s*=value;
    v.Mag(value);
}
Quaternion Quaternion::operator*(const float value){
    float scalar = s*value;
    Vector imaginary = v.MagV(value);

    return Quaternion(scalar, imaginary);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    float newS = s * other.s - v.DotProduct(other.v);
    Vector newV = v.Cross(other.v).AddV(other.v.MagV(s)).AddV(v.MagV(other.s));
    return Quaternion(newS, newV);
}

float Quaternion::norm() {
    float scalar = s*s;
    float imaginary = v.DotProduct(v);

    return sqrt(scalar+imaginary);
}

void Quaternion::normalize() {
    if(norm()!=0){
        float normValue = 1/norm();

        s*=normValue;
        v.Mag(normValue);
    }
}

void Quaternion::convertToUnitNormQuaternion() {
    float angle = DegreesToRad(s);
    v.Normalize();
    s=cosf(angle*0.5f);
    v=v.MagV(sinf(angle*0.5f));
}

Quaternion Quaternion::conjugate() {
    float scalar = s;
    Vector imaginary = v.MagV(-1);
    return Quaternion(scalar,imaginary);
}

Quaternion Quaternion::inverse() {
    float absoluteValue = norm();
    absoluteValue*=absoluteValue;
    absoluteValue=1/absoluteValue;

    Quaternion conjugateValue = conjugate();

    float scalar = conjugateValue.s*absoluteValue;
    Vector imaginary = conjugateValue.v.MagV(absoluteValue);

    return Quaternion(scalar, imaginary);
}



