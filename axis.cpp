#include "axis.h"
#include "vertex.h"
#include "vec3.h"
#include "matrix4x4.h"
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

Axis::Axis()
{
    createObject();
}

Axis::~Axis()
{
    delete[] mVertices;
}

void Axis::createObject()
{
    mNumberOfVertices = 6;
    mVertices = new Vertex[mNumberOfVertices]
    {
        // Positions                    // Colors                   //UVs
        {Vec3{-500.f, 0.f, 0.0f},      Vec3{1.0f, 0.0f, 0.0f},     Vec2{0.f, 0.f}},  // X-left
        {Vec3{ 500.f, 0.f, 0.0f},      Vec3{1.0f, 0.0f, 0.0f},     Vec2{0.f, 0.f}},  // X-right
        {Vec3{ 0.f,-500.f, 0.0f},      Vec3{0.0f, 1.0f, 0.0f},     Vec2{0.f, 0.f}},  // Y-bottom
        {Vec3{ 0.f, 500.f, 0.0f},      Vec3{0.0f, 1.0f, 0.0f},     Vec2{0.f, 0.f}},  // Y-top
        {Vec3{ 0.f, 0.f, -500.f},      Vec3{0.0f, 0.0f, 1.0f},     Vec2{0.f, 0.f}},  // Z-back
        {Vec3{  0.f, 0.f, 500.f},      Vec3{0.0f, 0.0f, 1.0f},     Vec2{0.f, 0.f}},  // Z-front
    };

    initializeOpenGLFunctions();

    glGenVertexArrays( 1, &mVAO);
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices
    glGenBuffers( 1, &mBufferObject );
    glBindBuffer( GL_ARRAY_BUFFER, mBufferObject );
    glBufferData( GL_ARRAY_BUFFER, mNumberOfVertices * sizeof( GLfloat ) * sizeof(Vertex),
                  mVertices, GL_STATIC_DRAW );  // 8 floats pr vertex
}

void Axis::drawObject()
{

}
