#include "BezierCurve.h"
#include <iostream>
#include <fstream>
#include "constants.h"

BezierCurve::BezierCurve(std::string fileName)
{
    std::string filePath = gsl::valuesFilePath + fileName;
    std::ifstream inData(filePath.c_str());
    float values[3]{};
    std::vector <Vec3> v;
    while(!inData.eof())
    {
        inData>>values[0]>>values[1]>>values[2];
        v.push_back(Vec3 (values[0], values[1], values[2]));
    }
    inData.close();
    for(int i = 0; i < 4; i++)
    {
        b[i] = v[i];
    }
    createObject();
}

BezierCurve::BezierCurve(std::vector<Vec3> v)
{
    b[0] = v[0];
    b[3] = v[v.size() - 1];

    b[1] = v[(v.size() / 3) - 1];
    b[2] = v[(2 * v.size() / 3) - 1];

    createObject();
}


void BezierCurve::createObject()
{
    std::vector <Vec3> dataPoints = createCurvePoints();
    mNumberOfVertices = dataPoints.size();

    mVertices = new Vertex[mNumberOfVertices];
    float a[3]{1.f, 0.f, 0.f};
    float increment = 1.f / mNumberOfVertices * 2.f;
    for(int i = 0; i < mNumberOfVertices; i++)
    {
        mVertices[i] = {dataPoints[i], Vec3{a[0], a[1], a[2]}, Vec2{0.f, 0.f}};

        if(a[0] > 0.f)
        {
            a[0] -= increment;
            a[1] += increment;
        }
        else
        {
            a[1] -= increment;
            a[2] += increment;
        }

    }

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

void BezierCurve::drawObject()
{

}

Vec3 BezierCurve::evaluateBezier(int degree, float t, Vec3 inC[4])
{
    Vec3 c[4];
    for(int i = 0; i < 4; i++)
    {
        c[i] = inC[i];
    }
    for(int k = 1; k <= degree; k++)
    {
        for(int i = 0; i < degree - k + 1; i++)
        {
            c[i] = c[i] * (1 - t) + c[i+1] * t;
        }
    }
    return c[0];
}

std::vector<Vec3> BezierCurve::createCurvePoints()
{
    std::vector <Vec3> v;
    for(float t = 0.f; t < 1.f; t+= 0.001f)
    {
        v.push_back(evaluateBezier(3, t, b));
    }
    return v;
}
