//
// Created by cheily on 30.03.2025.
//

#include <iostream>
#include "tasks.h"
#include "../rtx/Point.h"
#include "../rtx/Vector.h"
#include "../rtx/Sphere.h"
#include "../rtx/Plane.h"
#include "../rtx/Triangle.h"

using namespace std;

void printVector(Vector v){
    cout << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

void foto::task1() {

    Point p1(5.f,4.f,2.f);
    Point p2(2.f,1.f,2.f);

    Point p3(4.f,5.f,1.f);
    Point p4(2.f,3.f,1.f);

    Vector result;
    Vector v1(p1, p2);
    Vector v2(p3, p4);

    //v1.Normalize();
    //v2.Normalize();

    //result = v1.Cross(v2);

    //cout << result.x << " " << result.y << " " << result.z << endl;
    //cout << v1.AngleBetween(v2);


    Vector v1Copy = v1;
    Vector v2Copy = v2;
    cout << "2: " << endl;
    printVector(v1); cout << " + "; printVector(v2); cout << " = "; v1Copy.Add(v2); printVector(v1Copy); cout << endl;
    printVector(v2); cout << " + "; printVector(v1); cout << " = "; v2Copy.Add(v1); printVector(v2Copy); cout << endl; cout << endl;


    Vector v3(0.0f, 3.0f, 0.0f);
    Vector v4(5.0f, 5.0f, 0.0f);
    cout << "3: " << endl;
    cout << v3.AngleBetween(v4) << endl << endl;


    Vector v5(4.0f, 5.0f, 1.0f);
    Vector v6(4.0f, 1.0f, 3.0f);
    Vector cross = v5.Cross(v6);
    cout << "4: " << endl;
    printVector(cross); cout << endl; cout << endl;

    cross.Normalize();
    cout << "5: " << endl;
    printVector(cross); cout << endl; cout << endl;


    Vector center(0.0f,0.0f,0.0f);
    Sphere sphere(center, 10.0f);

    Vector origin(0.0f,0.0f,-20.0f);
    Vector direction1 = center.SubV(origin);
    Ray r1(origin, direction1);

    Vector parallel(0.0f,20.0f,-20.0f);
    Vector direction2 = parallel.SubV(origin);
    Ray r2(origin,direction2);

    cout << "11:" << endl;

    Vector intersection1;
    Vector intersection2;

    if(sphere.Hit(r1, 0.0f, 25.0f, intersection1)) {cout << "R1 przecina w: "; printVector(intersection1); cout << endl;}
    else cout << "R1 nie przecina. " << endl;
    if(sphere.Hit(r2, 0.0f, 25.0f, intersection2)) {cout << "R2 przecina w:"; printVector(intersection2); cout << endl;}
    else cout << "R2 nie przecina. " << endl;
    cout << endl;

    Vector origin2(0.0f,-10.0f,10.0f);
    Vector point(0.0f,10.0f,10.0f);
    Vector direction3 = point.SubV(origin2);
    Ray r3(origin2, direction3);

    cout << "12:" << endl;
    Vector intersection3;
    if(sphere.Hit(r3, 0.0f, 20.0f, intersection3)) {cout << "R3 przecina w: "; printVector(intersection3); cout << endl;}
    else cout << "R3 nie przecina. " << endl;
    cout << endl;


    Vector normal2(0.0f,-1.0f,-1.0f);
    Plane plane(normal2, 0.0f);

    Vector yAxis(0.0f, 1.0f, 0.0f);
    Vector zAxis(0.0f, 0.0f, 1.0f);
    Vector xAxis(1.0f, 0.0f, 0.0f);

    cout << "13:" << endl;

    cout << "Kat miedzy wektorem normalnym a osia Y: " << normal2.AngleBetween(yAxis) << endl;
    cout << "Kat miedzy wektorem normalnym a osia Z: " << normal2.AngleBetween(zAxis) << endl;
    cout << "Kat miedzy wektorem normalnym a osia X: " << normal2.AngleBetween(xAxis) << endl;
    cout << endl;

    cout << "14:" << endl;

    IntersectionResult resultVector = plane.Intersects(r2);
    if (resultVector.type == HIT) {
        std::cout << "Przecina w : "; printVector(resultVector.intersectionPoint); cout << endl;
    }
    else {
        std::cout << "Nie przecina.";
    }
    cout << endl;


    cout << "15: " << endl;

    cout << "Przypadek 1: ";
    Vector A(0.0f,0.0f,0.0f);
    Vector B(1.0f,0.0f,0.0f);
    Vector C(0.0f,1.0f,0.0f);
    Triangle tri(A,B,C);

    Vector P1(-1.0f,0.5f,0.0f);
    Vector P2(1.0f,0.5f,0.0f);
    Vector Direct = P1.SubV(P2);

    Ray ray(P1,P2);
    Vector intersectionTri;

    if(tri.IntersectTriangle(ray,intersectionTri)) cout << "przecina" << endl;
    else cout << "nie przecina" << endl;

    cout << "Przypadek 2: ";
    Vector P3(2.0f,-1.0f,0.0f);
    Vector P4(2.0f,2.0f,0.0f);
    Vector Direct2 = P4.SubV(P4);

    Ray ray2(P3,P4);
    Vector intersectionTri2;

    if(tri.IntersectTriangle(ray2,intersectionTri2)) cout << "przecina" << endl;
    else cout << "nie przecina" << endl;

    cout << "Przypadek 3: ";
    Vector P5(0.0f,0.0f,-1.0f);
    Vector P6(0.0f,0.0f,1.0f);
    Vector Direct3 = P5.SubV(P6);

    Ray ray3(P5,P6);
    Vector intersectionTri3;

    if(tri.IntersectTriangle(ray3,intersectionTri3)) cout << "przecina" << endl;
    else cout << "nie przecina" << endl;
}