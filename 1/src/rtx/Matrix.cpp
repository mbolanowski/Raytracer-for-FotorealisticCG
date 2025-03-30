#include "Matrix.h"

Matrix::Matrix(float e0, float e1, float e2, float e3,
               float e4, float e5, float e6, float e7,
               float e8, float e9, float e10, float e11,
               float e12, float e13, float e14, float e15){
    entries[0]=e0;
    entries[1]=e1;
    entries[2]=e2;
    entries[3]=e3;
    entries[4]=e4;
    entries[5]=e5;
    entries[6]=e6;
    entries[7]=e7;
    entries[8]=e8;
    entries[9]=e9;
    entries[10]=e10;
    entries[11]=e11;
    entries[12]=e12;
    entries[13]=e13;
    entries[14]=e14;
    entries[15]=e15;
}

Matrix::Matrix(const Matrix &mat){
    memcpy(entries, mat.entries, 16*sizeof(float));
}

Matrix::Matrix(const float * pF){
    memcpy(entries, pF, 16*sizeof(float));
}

Matrix Matrix::operator+(const Matrix &mat) const{
    return Matrix(entries[0] + mat.entries[0],
                  entries[1] + mat.entries[1],
                  entries[2] + mat.entries[2],
                  entries[3] + mat.entries[3],
                  entries[4] + mat.entries[4],
                  entries[5] + mat.entries[5],
                  entries[6] + mat.entries[6],
                  entries[7] + mat.entries[7],
                  entries[8] + mat.entries[8],
                  entries[9] + mat.entries[9],
                  entries[10] + mat.entries[10],
                  entries[11] + mat.entries[11],
                  entries[12] + mat.entries[12],
                  entries[13] + mat.entries[13],
                  entries[14] + mat.entries[14],
                  entries[15] + mat.entries[15]);
}

Matrix Matrix::operator*(const float f) const{
    return Matrix(entries[0] * f,
                  entries[1] * f,
                  entries[2] * f,
                  entries[3] * f,
                  entries[4] * f,
                  entries[5] * f,
                  entries[6] * f,
                  entries[7] * f,
                  entries[8] * f,
                  entries[9] * f,
                  entries[10] * f,
                  entries[11] * f,
                  entries[12] * f,
                  entries[13] * f,
                  entries[14] * f,
                  entries[15] * f);
}

Matrix Matrix::operator*(const Matrix &mat) const{
    if(entries[3] == 0.0f && entries[7] == 0.0f && entries[11] == 0.0f && entries[15] == 1.0f &&
    mat.entries[3] == 0.0f && mat.entries[7] == 0.0f && mat.entries[11] == 0.0f && mat.entries[15] == 1.0f){
        return Matrix(entries[0]*mat.entries[0]+entries[4]*mat.entries[1]+entries[8]*mat.entries[2],
                      entries[1]*mat.entries[0]+entries[5]*mat.entries[1]+entries[9]*mat.entries[2],
                      entries[2]*mat.entries[0]+entries[6]*mat.entries[1]+entries[10]*mat.entries[2],
                      0.0f,
                      entries[0]*mat.entries[4]+entries[4]*mat.entries[5]+entries[8]*mat.entries[6],
                      entries[1]*mat.entries[4]+entries[5]*mat.entries[5]+entries[9]*mat.entries[6],
                      entries[2]*mat.entries[4]+entries[6]*mat.entries[5]+entries[10]*mat.entries[6],
                      0.0f,
                      entries[0]*mat.entries[8]+entries[4]*mat.entries[9]+entries[8]*mat.entries[10],
                      entries[1]*mat.entries[8]+entries[5]*mat.entries[9]+entries[9]*mat.entries[10],
                      entries[2]*mat.entries[8]+entries[6]*mat.entries[9]+entries[10]*mat.entries[10],
                      0.0f,
                      entries[0]*mat.entries[12]+entries[4]*mat.entries[13]+entries[8]*mat.entries[14]+entries[12],
                      entries[1]*mat.entries[12]+entries[5]*mat.entries[13]+entries[9]*mat.entries[14]+entries[13],
                      entries[2]*mat.entries[12]+entries[6]*mat.entries[13]+entries[10]*mat.entries[14]+entries[14],
                      1.0f);
    }
}

void Matrix::LoadIdentity(void) {
    memset(entries, 0 ,16*sizeof(float));
    entries[0]=1.0f;
    entries[5]=1.0f;
    entries[10]=1.0f;
    entries[15]=1.0f;
}

void Matrix::setMatrixAsInverseOfGivenMatrix(const Matrix& m) {
 //3x3 Matrix

    float t1 = m.entries[0] * m.entries[4];
    float t2 = m.entries[0] * m.entries[7];
    float t3 = m.entries[3] * m.entries[1];
    float t4 = m.entries[6] * m.entries[1];
    float t5 = m.entries[3] * m.entries[2];
    float t6 = m.entries[6] * m.entries[2];

    float det = (t1 * m.entries[8] - t2 * m.entries[5] -
                 t3 * m.entries[8] + t4 * m.entries[5] +
                 t5 * m.entries[7] - t6 * m.entries[4]);

    if (det == 0.0) return;

    float invd = 1.0f / det;

    float m0 = (m.entries[4] * m.entries[8] - m.entries[7] * m.entries[5]) * invd;
    float m3 = -(m.entries[3] * m.entries[8] - m.entries[6] * m.entries[5]) * invd;
    float m6 = (m.entries[3] * m.entries[7] - m.entries[6] * m.entries[4]) * invd;
    float m1 = -(m.entries[1] * m.entries[8] - m.entries[7] * m.entries[2]) * invd;
    float m4 = (m.entries[0] * m.entries[8] - t6) * invd;
    float m7 = -(t2 - t4) * invd;

    float m2 = (m.entries[1] * m.entries[5] - m.entries[4] * m.entries[2]) * invd;
    float m5 = -(m.entries[0] * m.entries[5] - t5) * invd;
    float m8 = (t1 - t3) * invd;

    entries[0] = m0;
    entries[3] = m3;
    entries[6] = m6;

    entries[1] = m1;
    entries[4] = m4;
    entries[7] = m7;

    entries[2] = m2;
    entries[5] = m5;
    entries[8] = m8;
}

Matrix Matrix::getInverseOfMatrix() const {
    Matrix result;
    result.setMatrixAsInverseOfGivenMatrix(*this);
    return result;
}

void Matrix::invertMatrix() {
    setMatrixAsInverseOfGivenMatrix(*this);
}

void Matrix::setMatrixAsTransposeOfGivenMatrix(const Matrix m) {
    entries[0] = m.entries[0];
    entries[3] = m.entries[1];
    entries[6] = m.entries[2];

    entries[1] = m.entries[3];
    entries[4] = m.entries[4];
    entries[7] = m.entries[5];

    entries[2] = m.entries[6];
    entries[5] = m.entries[7];
    entries[8] = m.entries[8];
}

Matrix Matrix::getTransposeOfMatrix() const {
    Matrix result;
    result.setMatrixAsTransposeOfGivenMatrix(*this);
    return result;
}

void Matrix::SetTranslationPart(const Vector &translation){
    entries[12] = translation.x;
    entries[13] = translation.y;
    entries[14] = translation.z;
}

void Matrix::SetScale(const Vector &scaleFactor) {
    LoadIdentity();

    entries[0] = scaleFactor.x;
    entries[5] = scaleFactor.y;
    entries[10] = scaleFactor.z;
}

void Matrix::SetUniformScale(const float scaleFactor){
    LoadIdentity();

    entries[0]=entries[5]=entries[10]=scaleFactor;
}

void Matrix::SetRotationAxis(const double angle, Vector &axis) {
    // Normalize the axis vector
    Vector u = axis.NormalizeV();

    // Convert angle from degrees to radians and compute trig functions
    float sinAngle = static_cast<float>(sin(M_PI * angle / 180.0));
    float cosAngle = static_cast<float>(cos(M_PI * angle / 180.0));
    float oneMinusCosAngle = 1.0f - cosAngle;

    LoadIdentity();

    entries[0] = (u.x) * (u.x) + cosAngle * (1.0f - (u.x) * (u.x));
    entries[4] = (u.x) * (u.y) * (oneMinusCosAngle) - sinAngle * u.z;
    entries[8] = (u.x) * (u.z) * (oneMinusCosAngle) + sinAngle * u.y;

    entries[1] = (u.x) * (u.y) * (oneMinusCosAngle) + sinAngle * u.z;
    entries[5] = (u.y) * (u.y) + cosAngle * (1.0f - (u.y) * (u.y));
    entries[9] = (u.y) * (u.z) * (oneMinusCosAngle) - sinAngle * u.x;

    entries[2] = (u.x * u.z * oneMinusCosAngle) - sinAngle * u.y;
    entries[6] = (u.y * u.z * oneMinusCosAngle) + sinAngle * u.x;
    entries[10] = (u.z * u.z) + cosAngle * (1.0f - (u.z) * (u.z));
}

void Matrix::SetRotationX(const double angle) {
    LoadIdentity();

    entries[5] = (float)cos(M_PI*angle/180);
    entries[6] = (float)sin(M_PI*angle/180);

    entries[9] = -entries[6];
    entries[10] = entries[5];
}

void Matrix::SetRotationY(const double angle) {
    LoadIdentity();

    entries[0] = (float)cos(M_PI*angle/180);
    entries[2] = -(float)sin(M_PI*angle/180);

    entries[8] = -entries[2];
    entries[10] = entries[0];
}

void Matrix::SetRotationZ(const double angle) {
    LoadIdentity();

    entries[0] = (float)cos(M_PI*angle/180);
    entries[1] = (float)sin(M_PI*angle/180);

    entries[4] = -entries[1];
    entries[5] = entries[0];
}

void Matrix::printMatrix() {
    for(int i = 0; i < 4; i++)
    {
        std::cout << entries[i] << " " << entries[i+1] << " " << entries[i+2] << " " << entries[i+3] << std::endl;
    }
}