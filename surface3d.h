#ifndef SURFACE3D_H
#define SURFACE3D_H

#include "sceneobject.h"
#include <cmath>
#include "vertex.h"
#include "vec2.h"
#include <vector>
#include <fstream>
#include <constants.h>

struct TriangleS
{
    TriangleS(int inNodes[], int inNeighbors[])
    {
        for(int i = 0; i < 3; i++)
        {
            nodes[i] = inNodes[i];
            neighbors[i] = inNeighbors[i];
        }
    }

    int nodes[3];
    int neighbors[3];
};

class surface3D : public SceneObject
{
private:
    int xMin, xMax, yMin, yMax;

    float interval;

    int mNumberOfIndices;

    std::vector<TriangleS> Triangles;

    GLuint mElementBufferObject;
    GLuint mNormalBufferObject;

public:
    surface3D(int inXMin, int inXMax, int inYMin, int inYMax, float inInterval = 1.f);
    ~surface3D();
    void createObject() override;
    void drawObject() override;
    float function(float x, float y);
    std::vector<Vec3> getSurfaceNormals();

    void writeToFile(std::string fileName, unsigned int indices[], int arrayLength);

    int getNumberofIndices();

    void populateTrinangleStruct(std::string fileName);

    int findTriangle(int p, Vec3 q, std::vector<Vec3> &bezierValues);

    //GLuint mNormalVAO{0};

};

#endif // SURFACE3D_H
