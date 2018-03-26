#include "plane.h"

Plane::Plane()
{
    createObject();
}

Plane::~Plane()
{
    delete[] mVertices;
}

void Plane::createObject()
{
    mNumberOfVertices = 6;

    mVertices = new Vertex[mNumberOfVertices]
    {
        // Positions                // Colors                   // UVs
        {Vec3{0.5f, 0.5f, 0.0f},    Vec3{0.0f, 0.2f, 0.8f},     Vec2{0.f, 0.f}},
        {Vec3{0.5f, -0.5f, 0.0f},   Vec3{0.0f, 0.2f, 0.8f},     Vec2{0.f, 0.f}},
        {Vec3{-0.5f, 0.5f, 0.0f},   Vec3{0.0f, 0.8f, 0.0f},     Vec2{0.f, 0.f}},

        {Vec3{0.5f, -0.5f, 0.0f},    Vec3{0.0f, 0.8f, 0.2f},     Vec2{0.f, 0.f}},
        {Vec3{-0.5f, -0.5f, 0.0f},   Vec3{0.0f, 0.8f, 0.2f},     Vec2{0.f, 0.f}},
        {Vec3{-0.5f, 0.5f, 0.0f},    Vec3{0.0f, 0.0f, 0.8f},     Vec2{0.f, 0.f}}
    };

    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, mBufferObject);
    glBufferData(GL_ARRAY_BUFFER, mNumberOfVertices * sizeof(GLfloat) * sizeof(Vertex), mVertices, GL_STATIC_DRAW);
}

void Plane::drawObject()
{

}
