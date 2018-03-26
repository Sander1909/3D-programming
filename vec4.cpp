#include "vec4.h"
#include "vec3.h"

Vec4::Vec4(GLfloat x_in, GLfloat y_in, GLfloat z_in, GLfloat w_in)
    : x{x_in}, y{y_in}, z{z_in}, w{w_in}
{
}

Vec4::Vec4(Vec3 vec3_in, GLfloat w_in)
    : x{vec3_in.getX()}, y{vec3_in.getY()}, z{vec3_in.getZ()}, w{w_in}
{
}

GLfloat Vec4::getX() const
{
    return x;
}

void Vec4::setX(const GLfloat &value)
{
    x = value;
}

GLfloat Vec4::getY() const
{
    return y;
}

void Vec4::setY(const GLfloat &value)
{
    y = value;
}

GLfloat Vec4::getZ() const
{
    return z;
}

void Vec4::setZ(const GLfloat &value)
{
    z = value;
}

GLfloat Vec4::getW() const
{
    return w;
}
void Vec4::setW(const GLfloat &value)
{
    if(value == 0.f || value == 1.f)    //w should be only 0 or 1
        w = value;
}
