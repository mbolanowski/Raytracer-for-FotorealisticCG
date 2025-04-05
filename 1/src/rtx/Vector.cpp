#include "Vector.h"
#include "Quaternion.h"

Vector::Vector() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
Vector::Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {}
Vector::Vector(Point p1, Point p2) : x(p1.x - p2.x), y(p1.y - p2.y), z(p1.z - p2.z) {}
Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}
Vector::~Vector() noexcept {}

void Vector::Add(const Vector &v){
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector Vector::AddV(Vector v){
    Vector result;

    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;

    return result;
}

void Vector::Sub(const Vector &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector Vector::SubV(Vector v){
    Vector result;

    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;

    return result;
}

void Vector::Div(float f){
    if(f != 0){
        x /= f;
        y /= f;
        z /= f;
    }
    else{
        std::cout << "Can't divide by 0" << std::endl;
    }
}

Vector Vector::DivV(float f){
    Vector result;
    if(f != 0){
        result.x = x / f;
        result.y = y / f;
        result.z = z / f;
        return result;
    }
    else{
        std::cout << "Can't divide by 0" << std::endl;
        return result;
    }
}

void Vector::Mag(float f){
    x *= f;
    y *= f;
    z *= f;
}

Vector Vector::MagV(float f) const {
    Vector result;
    result.x = x * f;
    result.y = y * f;
    result.z = z * f;
    return result;
}

float Vector::Length() const {
    return (float)sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

void Vector::Normalize(){
    float n = Length();
    if(n != 0){
        Div(n);
    }
    else{
        std::cout << "Can't divide by 0" << std::endl;
    }
}

Vector Vector::NormalizeV(){
    float n = Length();
    Vector returned;

    if(n != 0){
        returned = DivV(n);
    }
    else{
        std::cout << "Can't divide by 0" << std::endl;
    }

    return returned;
}

Vector Vector::Dot(Vector v){
    Vector result;
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result;
}

float Vector::DotProduct(Vector v) const {
    Vector result;
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result.x + result.y + result.z;
}

Vector Vector::Cross(Vector v) const {
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vector::AngleBetween(Vector v){
    float dotP = DotProduct(v);

    float Length1 = Length();
    float Length2 = v.Length();

    float cos = dotP / (Length1 * Length2);

    cos = fmax(-1.0f, fmin(1.0f, cos));

    return acos(cos) * (180.0f / M_PI);
}

Vector Vector::rotateVectorAboutAngleAndAxis(float uAngle, Vector &uAxis){
    Quaternion p(0,(*this));

    uAxis.Normalize();

    Quaternion q(uAngle, uAxis);

    q.convertToUnitNormQuaternion();

    Quaternion qInverse=q.inverse();

    Quaternion rotatedVector=q*p*qInverse;

    return rotatedVector.v;
}


bool Vector::operator==(const Vector &v) const {
    return x == v.x && y == v.y && z == v.z;
}

Vector Vector::operator-() const {
    return {-x, -y, -z};
}

Vector Vector::operator+(const Vector &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vector Vector::operator-(const Vector &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

Vector Vector::operator*(float f) const {
    return {x * f, y * f, z * f};
}

bool Vector::operator<(const Vector &v) const {
    return Length() < v.Length();
}

bool Vector::operator>(const Vector &v) const {
    return Length() > v.Length();
}
