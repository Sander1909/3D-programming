#include "vec3.h"
#include "matrix4x4.h"
#include <cmath>

#define M_PI 3.14159265358979323846     //Visual studio

Vec3::Vec3(GLfloat x_in, GLfloat y_in, GLfloat z_in)
    : x{x_in}, y{y_in}, z{z_in}
{
}

const Vec3& Vec3::operator =(const Vec3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

Vec3 Vec3::operator +(const Vec3 &v) const
{
    Vec3 u;
    u.x = x + v.x;
    u.y = y + v.y;
    u.z = z + v.z;
    return u;
}

Vec3 Vec3::operator -(const Vec3 &v) const
{
    Vec3 u;
    u.x = x - v.x;
    u.y = y - v.y;
    u.z = z - v.z;
    return u;
}

Vec3 Vec3::operator ^(const Vec3 &v) const
{
    Vec3 w;
    w.x =  y*v.z - z*v.y;
    w.y =  z*v.x - x*v.z;
    w.z =  x*v.y - y*v.x;
    return w;
}

void Vec3::normalize()
{
    GLfloat d = x*x+y*y+z*z;
    d = sqrt(d);
    if (d>0.0)
    {
        x=x/d;
        y=y/d;
        z=z/d;
    }
}

Vec3 Vec3::normalized()
{
    Vec3 normalized;
    GLfloat d = x*x+y*y+z*z;
    d = sqrt(d);
    if (d>0.0)
    {
        normalized.x=x/d;
        normalized.y=y/d;
        normalized.z=z/d;
    }
    return normalized;
}

void Vec3::rotateX(double angle)
{
    Vec3 dir;
    angle = deg2Rad(angle);
    //qDebug() << "Angle: " << angle;
    dir.x = x;
    dir.y = y * cos(angle) + z * -sin(angle);
    dir.z = y * sin(angle) + z * cos(angle) ;

    x = dir.x;
    y = dir.y;
    z = dir.z;
}

void Vec3::rotateY(double angle)
{
    Vec3 dir;
    angle = deg2Rad(angle);
    //qDebug() << "Angle: " << angle;
    dir.x = x * cos(angle) + z * sin(angle);
    dir.y = y;
    dir.z = x * -sin(angle) + z * cos(angle);

    x = dir.x;
    y = dir.y;
    z = dir.z;
}

void Vec3::rotateZ(double angle)
{
    Vec3 dir;
    angle = deg2Rad(angle);
    //qDebug() << "Angle: " << angle;
    dir.x = x * cos(angle) + y * -sin(angle);
    dir.y = x * sin(angle) + y * cos(angle);
    dir.z = z;

    x = dir.x;
    y = dir.y;
    z = dir.z;
}

Vec3 Vec3::operator *(Matrix4x4 q) const
{
    q = q;  //just noncense for now to get rid of warning

    //            -------------- MATRIX MULTIPLICATION ----------------------
    //            | 0  | 1  | 2  | 3  |
    //            | 4  | 5  | 6  | 7  |        X         | x  | y  | z  | 1 |
    //            | 8  | 9  | 10 | 11 |
    //            | 12 | 13 | 14 | 15 |


//    float _x,_y,_z,_w;
//    _x = (q.column(0).x() * x + q.column(0).y() * y + q.column(0).z() * z + q.column(0).w());
//    _y = (q.column(1).x() * x + q.column(1).y() * y + q.column(1).z() * z + q.column(1).w());
//    _z = (q.column(2).x() * x + q.column(2).y() * y + q.column(2).z() * z + q.column(2).w());
//    _w = (q.column(3).x() * x + q.column(3).y() * y + q.column(3).z() * z + q.column(3).w());

//    if(_w == 1.0f)
//        return Vec3(_x, _y, _z);
//    else
//        return Vec3(_x/_w, _y/_w, _z/_w);
    return *this;   //just noncense for now to get rid of warning
}

float Vec3::length()
{
    return sqrt(x*x+y*y+z*z);
}

double Vec3::rad2Deg(double &rad)
{
    return (rad * 180)/M_PI;    //M_PI is in cmath
}

double Vec3::deg2Rad(double &deg)
{
    return (deg * M_PI)/180;    //M_PI is in cmath
}

GLfloat Vec3::getX() const
{
    return x;
}

void Vec3::setX(const GLfloat &value)
{
    x = value;
}

GLfloat Vec3::getY() const
{
    return y;
}

void Vec3::setY(const GLfloat &value)
{
    y = value;
}

GLfloat Vec3::getZ() const
{
    return z;
}

void Vec3::setZ(const GLfloat &value)
{
    z = value;
}

Vec3 Vec3::operator *(float c) const
{
    return Vec3(x*c, y*c, z*c);
}

Vec3 Vec3::operator /(float c) const
{
    return Vec3(x/c, y/c, z/c);
}

float Vec3::operator *(const Vec3 &v) const
{
    return x*v.x + y*v.y + z*v.z;
}
