#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <fstream>
#include "vec3.h"
#include "vec2.h"
#include <QtGui/qopengl.h> // for GLfloat

class Vertex
{
public:
    Vertex();
    Vertex(Vec3 a, Vec3 b, Vec2 c);
    ~Vertex();
    void set_xyz(GLfloat* xyz);
    void set_xyz(GLfloat x, GLfloat y, GLfloat z);
    void set_xyz(Vec3 xyz_in);
    void set_rgb(GLfloat* rgb);
    void set_rgb(GLfloat r, GLfloat g, GLfloat b);
    void set_normal(GLfloat* normal);
    void set_normal(GLfloat x, GLfloat y, GLfloat z);
    void set_normal(Vec3 normal_in);
    void set_st(GLfloat* st);
    void set_st(GLfloat s, GLfloat t);
    void set_uv(GLfloat u, GLfloat v);
    Vec3 get_xyz();
    GLfloat get_x();
    GLfloat get_y();
    GLfloat get_z();

private:
    Vec3 mXYZ;
    Vec3 mNormal;
    Vec2 mST;

    friend std::ostream& operator<< (std::ostream&, const Vertex&);
//    friend std::istream& operator>> (std::istream&, Vertex&);

};

#endif // VERTEX_H
