#ifndef VEC4_H
#define VEC4_H

#include <cmath>
#include <iostream>
#include <cassert>

#include <QtGui/qopengl.h> // for GLfloat

class Matrix4x4;
class Vec3;

class Vec4
{
public:
    Vec4(GLfloat x_in=0.f, GLfloat y_in=0.f, GLfloat z_in=0.f, GLfloat w_in = 0.f);
    Vec4(Vec3 vec3_in, GLfloat w_in = 1.f);

    const Vec4 &operator = (const Vec4& v);
    Vec4 operator + (const Vec4& v) const;
    Vec4 operator - (const Vec4& v) const;

    Vec4 operator ^ (const Vec4& v) const;  // Cross product

    void normalize();
    Vec4 normalized();

    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

    float operator * (const Vec4& v) const; // Dot product
    Vec4 operator * (float c) const;
    Vec4 operator * (Matrix4x4 q) const;

    float length();

    double rad2Deg(double &rad);
    double deg2Rad(double &deg);

    //Operator overloading as friendfunction
    friend std::ostream &operator<<(std::ostream &output, const Vec4 &vIn )
    {
        output << "X = " << vIn.x << ", Y = " << vIn.y <<
                  ", Z = " << vIn.z << ", W = " << vIn.w;
        return output;
    }

    GLfloat& operator[] (const int index)
    {
        assert(index <4 && index >=0);

        switch (index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        case 3:
            return w;
            break;
        }
        return x;      //to silence compiler warnings
    }
    const GLfloat& operator[] (const int index) const
    {
        assert(index <4 && index >=0);

        switch (index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        case 3:
            return w;
            break;
        }
        return x;   //to silence compiler warnings
    }

    GLfloat getX() const;
    void setX(const GLfloat &value);
    GLfloat getY() const;
    void setY(const GLfloat &value);
    GLfloat getZ() const;
    void setZ(const GLfloat &value);
    GLfloat getW() const;
    void setW(const GLfloat &value);

private:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

#endif // VEC4_H
