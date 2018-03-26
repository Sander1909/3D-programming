#include "triangle.h"
#include "vertex.h"
#include "vec3.h"
#include "matrix4x4.h"
#include <QMatrix4x4>

Triangle::Triangle()
{
    createObject();
}

Triangle::~Triangle()
{
    delete[] mVertices;
}

void Triangle::createObject()
{
    mNumberOfVertices = 3;
    mVertices = new Vertex[mNumberOfVertices]
    {
            // Positions                    // Colors                   //UVs
        {Vec3{-0.5f, -0.5f, 0.0f},      Vec3{1.0f, 0.0f, 0.0f},     Vec2{0.f, 0.f}},  // Bottom Left
        {Vec3{0.5f, -0.5f, 0.0f},       Vec3{0.0f, 1.0f, 0.0f},     Vec2{1.f, 0.f}}, // Bottom Right
        {Vec3{0.0f,  0.5f, 0.0f},       Vec3{0.0f, 0.0f, 1.0f},     Vec2{0.5f, 1.f}}   // Top
    };

    //Set up the OpenGL part:
    initializeOpenGLFunctions();

    glGenVertexArrays( 1, &mVAO);
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices
    glGenBuffers( 1, &mBufferObject );
    glBindBuffer( GL_ARRAY_BUFFER, mBufferObject );
    glBufferData( GL_ARRAY_BUFFER, mNumberOfVertices * sizeof( GLfloat ) * sizeof(Vertex),
                  mVertices, GL_STATIC_DRAW );  // 8 floats pr vertex
}

void Triangle::drawObject()
{

}

