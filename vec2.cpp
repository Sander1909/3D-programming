#include "vec2.h"

Vec2::Vec2(GLfloat x_in, GLfloat y_in) : x{x_in}, y{y_in} { }

const Vec2 &Vec2::operator =(const Vec2 &v)
{
    x = v.x;
    y = v.y;
    return *this;
}

Vec2 Vec2::operator +(const Vec2 &v) const
{
    Vec2 u;
    u.x = x + v.x;
    u.y = y + v.y;
    return u;
}

Vec2 Vec2::operator -(const Vec2 &v) const
{
    Vec2 u;
    u.x = x - v.x;
    u.y = y - v.y;
    return u;
}

GLfloat Vec2::getX() const
{
    return x;
}

void Vec2::setX(const GLfloat &value)
{
    x = value;
}

GLfloat Vec2::getY() const
{
    return y;
}

void Vec2::setY(const GLfloat &value)
{
    y = value;
}
