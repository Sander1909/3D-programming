#include "octahedron.h"
#include "cmath"
#include "vertex.h"
#include "vec3.h"
#include "matrix4x4.h"
#include <QMatrix4x4>

Octahedron::Octahedron(int n) : mRecursions(n), mIndex(0)
{
    createObject();
}

Octahedron::~Octahedron()
{
    delete[] mVertices;
}

void Octahedron::createObject()
{
    mNumberOfVertices = 3 * 8 * pow(4, mRecursions);
    mVertices = new Vertex[mNumberOfVertices];
    makeUnitOctahedron();

    initializeOpenGLFunctions();

    glGenVertexArrays( 1, &mVAO);
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices
    glGenBuffers( 1, &mBufferObject );
    glBindBuffer( GL_ARRAY_BUFFER, mBufferObject );
    glBufferData( GL_ARRAY_BUFFER, mNumberOfVertices * sizeof( GLfloat ) * sizeof(Vertex),
                  mVertices, GL_STATIC_DRAW );  // 8 floats pr vertex
}

void Octahedron::drawObject()
{

}

void Octahedron::makeTriangle(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
    mVertices[mIndex].set_xyz(v1.getX(), v1.getY(), v1.getZ());
    mVertices[mIndex].set_normal(v1.getX(), v1.getY(), v1.getZ());
    mVertices[mIndex].set_st(0.0f, 0.0f);
    ++mIndex;
    mVertices[mIndex].set_xyz(v2.getX(), v2.getY(), v2.getZ());
    mVertices[mIndex].set_normal(v2.getX(), v2.getY(), v2.getZ());
    mVertices[mIndex].set_st(1.0f, 0.0f);
    ++mIndex;
    mVertices[mIndex].set_xyz(v3.getX(), v3.getY(), v3.getZ());
    mVertices[mIndex].set_normal(v3.getX(), v3.getY(), v3.getZ());
    mVertices[mIndex].set_st(0.5f, 1.0f);
    ++mIndex;
}

void Octahedron::subDivide(const Vec3 &a, const Vec3 &b, const Vec3 &c, int n)
{
    if (n>0) {
        Vec3 v1 = a+b; v1.normalize();
        Vec3 v2 = a+c; v2.normalize();
        Vec3 v3 = c+b; v3.normalize();
        subDivide(a, v1, v2, n-1);
        subDivide(c, v2, v3, n-1);
        subDivide(b, v3, v1, n-1);
        subDivide(v3, v2, v1, n-1);
    } else {
        makeTriangle(a, b, c);
    }
}

void Octahedron::makeUnitOctahedron()
{
    Vec3 v0(0, 0, 1);
    Vec3 v1(1, 0, 0);
    Vec3 v2(0, 1, 0);
    Vec3 v3(-1, 0, 0);
    Vec3 v4(0, -1, 0);
    Vec3 v5(0, 0, -1);

    subDivide(v0, v1, v2, mRecursions);
    subDivide(v0, v2, v3, mRecursions);
    subDivide(v0, v3, v4, mRecursions);
    subDivide(v0, v4, v1, mRecursions);
    subDivide(v5, v2, v1, mRecursions);
    subDivide(v5, v3, v2, mRecursions);
    subDivide(v5, v4, v3, mRecursions);
    subDivide(v5, v1, v4, mRecursions);
}
