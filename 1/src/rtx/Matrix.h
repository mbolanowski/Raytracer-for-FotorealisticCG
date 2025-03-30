//
// Created by mbola on 3/24/2025.
//

#ifndef INC_2_MATRIX_H
#define INC_2_MATRIX_H

#include <cstring>
#include "Vector.h"

class Matrix{
public:
    float entries[16];

    Matrix(){}
    Matrix(float e0, float e1, float e2, float e3,
           float e4, float e5, float e6, float e7,
           float e8, float e9, float e10, float e11,
           float e12, float e13, float e14, float e15);
    Matrix(const float * f);
    Matrix(const Matrix &mat);
    ~Matrix(){}

    Matrix operator+(const Matrix &mat) const;
    Matrix operator*(const float f) const;
    Matrix operator*(const Matrix &mat) const;
    void LoadIdentity(void);
    void setMatrixAsInverseOfGivenMatrix(const Matrix& m);
    Matrix getInverseOfMatrix() const;
    void invertMatrix();

    void setMatrixAsTransposeOfGivenMatrix(const Matrix m);
    Matrix getTransposeOfMatrix() const;

    void SetTranslationPart(const Vector &translation);
    void SetScale(const Vector &scaleFactor);
    void SetUniformScale(const float scaleFactor);

    void SetRotationAxis(const double angle, Vector &axis);
    void SetRotationX(const double angle);
    void SetRotationY(const double angle);
    void SetRotationZ(const double angle);

    void printMatrix();
};

#endif //INC_2_MATRIX_H
