#include "matrix4x4.h"
#include <cmath>
#include <utility>
#include <cassert>

#define M_PI 3.14159265358979323846     //Visual Studio did not find it...

Matrix4x4::Matrix4x4()
{
}

Matrix4x4 Matrix4x4::identity()
{
    for (int c{0}; c<4;++c)
        for (int r{0}; r<4;++r)
            matrix[r + c*4] = 0.f;

    for (int a{0}; a<4;++a)
        matrix[a + a*4] = 1.f;
    return *this;
}

void Matrix4x4::translateX(GLfloat x)
{
    matrix[12] += x;
}

void Matrix4x4::translateY(GLfloat y)
{
    matrix[13] += y;
}

void Matrix4x4::translateZ(GLfloat z)
{
    matrix[14] += z;
}

void Matrix4x4::rotateX(GLfloat degrees)
{
    GLfloat rad = (degrees * M_PI)/180;
    matrix[5] = cos(rad);
    matrix[9] = -sin(rad);
    matrix[6] = sin(rad);
    matrix[10] = cos(rad);
}

void Matrix4x4::rotateY(GLfloat degrees)
{
    GLfloat rad = (degrees * M_PI)/180;
    matrix[0] = cos(rad);
    matrix[8] = sin(rad);
    matrix[2] = -sin(rad);
    matrix[10] = cos(rad);
}

void Matrix4x4::rotateZ(GLfloat degrees)
{
    GLfloat rad = (degrees * M_PI)/180;
    matrix[0] = cos(rad);
    matrix[4] = -sin(rad);
    matrix[1] = sin(rad);
    matrix[5] = cos(rad);
}

void Matrix4x4::scale(GLfloat uniformScale)
{
    matrix[0] = uniformScale;
    matrix[5] = uniformScale;
    matrix[10] = uniformScale;
    matrix[15] = 1.f;

}

void Matrix4x4::scale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
    matrix[0] = scaleX;
    matrix[5] = scaleY;
    matrix[10] = scaleZ;
    matrix[15] = 1.f;
}

void Matrix4x4::transpose()
{
    std::swap(matrix[1], matrix[4]);
    std::swap(matrix[2], matrix[8]);
    std::swap(matrix[3], matrix[12]);

    std::swap(matrix[6], matrix[9]);
    std::swap(matrix[7], matrix[13]);
    std::swap(matrix[11], matrix[14]);
}
//https://stackoverflow.com/questions/18404890/how-to-build-perspective-projection-matrix-no-api
void Matrix4x4::perspective(GLfloat verticalAngle, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane)
{
    //checking numbers for no division on zero:
    if (verticalAngle <= 0.f)
        verticalAngle = 30.f;
    if (aspectRatio <= 0.f)
        aspectRatio = 1.3f;
    if (farPlane == nearPlane)
    {
        nearPlane = 1.f;
        farPlane = 100.f;
    }

    GLfloat frustumDepth = farPlane - nearPlane;
    GLfloat oneOverDepth = 1 / frustumDepth;

    identity();
    matrix[5] = 1 / tan(0.5f * verticalAngle) ;
    matrix[0] = matrix[5] / aspectRatio;
    matrix[10] = farPlane * oneOverDepth;
    matrix[14] = (-farPlane * nearPlane) * oneOverDepth;;
    matrix[15] = 0.f ;
}

void Matrix4x4::translate(GLfloat x, GLfloat y, GLfloat z)
{
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;
}
