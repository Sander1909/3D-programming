#ifndef VEC3_H
#define VEC3_H

#include <QtGui/qopengl.h> // for GLfloat

#include <cmath>
#include <iostream>

class Matrix4x4;

class Vec3
{
public:
    Vec3(GLfloat x_in=0.0, GLfloat y_in=0.0, GLfloat z_in=0.0);

    const Vec3 &operator = (const Vec3& v);
    Vec3 operator + (const Vec3& v) const;
    Vec3 operator - (const Vec3& v) const;

    Vec3 operator ^ (const Vec3& v) const;  // Cross product

    void normalize();
    Vec3 normalized();

    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);

    float operator * (const Vec3& v) const; // Dot product
    Vec3 operator * (float c) const;
    Vec3 operator / (float c) const;
    Vec3 operator * (Matrix4x4 q) const;

    float length();

    double rad2Deg(double &rad);
    double deg2Rad(double &deg);

    //Operator overloading as friendfunction
    friend std::ostream &operator<<(std::ostream &output, const Vec3 &vIn )
    {
        output << "X = " << vIn.x << ", Y = " << vIn.y << ", Z = " << vIn.z;;
        return output;
    }

    GLfloat getX() const;
    void setX(const GLfloat &value);
    GLfloat getY() const;
    void setY(const GLfloat &value);
    GLfloat getZ() const;
    void setZ(const GLfloat &value);

private:
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

#endif // VEC3_H
