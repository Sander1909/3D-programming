#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(Vec3 a, Vec3 b , Vec2 c)
{
    mXYZ = a;
    mNormal = b;
    mST = c;
}

Vertex::~Vertex()
{
    //qDebug() << "Vertex::~Vertex()";
}

void Vertex::set_xyz(GLfloat* xyz)
{
    mXYZ.setX(xyz[0]);
    mXYZ.setY(xyz[1]);
    mXYZ.setZ(xyz[2]);
}

void Vertex::set_xyz(GLfloat x, GLfloat y, GLfloat z)
{
    mXYZ.setX(x); mXYZ.setY(y); mXYZ.setZ(z);
}

void Vertex::set_xyz(Vec3 xyz_in)
{
    mXYZ = xyz_in;
}

void Vertex::set_rgb(GLfloat* rgb)
{
    mNormal.setX(rgb[0]);
    mNormal.setY(rgb[1]);
    mNormal.setZ(rgb[2]);
}

void Vertex::set_rgb(GLfloat r, GLfloat g, GLfloat b)
{
    mNormal.setX(r); mNormal.setY(g); mNormal.setZ(b);
}

void Vertex::set_normal(GLfloat* normal)
{
    mNormal.setX(normal[0]);
    mNormal.setY(normal[1]);
    mNormal.setZ(normal[2]);
}

void Vertex::set_normal(GLfloat x, GLfloat y, GLfloat z)
{
    mNormal.setX(x); mNormal.setY(y); mNormal.setZ(z);
}

void Vertex::set_normal(Vec3 normal_in)
{
    mNormal = normal_in;
}

void Vertex::set_st(GLfloat* st)
{
    mST.setX(st[0]);
    mST.setY(st[1]);
}

void Vertex::set_st(GLfloat s, GLfloat t)
{
    mST.setX(s); mST.setY(t);
}

void Vertex::set_uv(GLfloat u, GLfloat v)
{
    mST.setX(u); mST.setY(v);
}

Vec3 Vertex::get_xyz()
{

    return mXYZ;
}

GLfloat Vertex::get_x()
{
    return mXYZ.getX();
}

GLfloat Vertex::get_y()
{
    return mXYZ.getY();
}

GLfloat Vertex::get_z()
{
    return mXYZ.getZ();
}

std::ostream& operator<< (std::ostream& os, const Vertex& v)
{
   os << "(" << v.mXYZ.getX() << ", " << v.mXYZ.getY() << ", " << v.mXYZ.getZ() << ") ";
   os << "(" << v.mNormal.getX() << ", " << v.mNormal.getY() << ", " << v.mNormal.getZ() << ") ";
//   os << "(" << v.mST.getX() << ", " << v.mST.getY() << ") ";
   return os;
}
//std::istream& operator>> (std::istream& is, Vertex& v)
//{
//// Four temp variables to hold parentecis and comma
//   char dum, dum2, dum3, dum4;
//   is >> dum >> v.mXYZ >> dum2 >> v.mXYZ.y >> dum3 >> v.mXYZ.z >> dum4;
//   is >> dum >> v.mNormal.x >> dum2 >> v.mNormal.y >> dum3 >> v.mNormal.z >> dum4;
//   is >> dum >> v.mST.x >> dum2 >> v.mST.y >> dum3;

//   return is;
//}
