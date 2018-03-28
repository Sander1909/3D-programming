#include "surface3d.h"

surface3D::surface3D(int inXMin, int inXMax, int inYMin, int inYMax, float inInterval)
{
    xMin = inXMin;
    xMax = inXMax;
    yMin = inYMin;
    yMax = inYMax;
    interval = inInterval;

    mNumberOfIndices = (yMax - yMin - 1) * (xMax - xMin - 1) * 2 * 3;

    createObject();
}

surface3D::~surface3D()
{
    delete[] mVertices;
}

void surface3D::createObject()
{
    mNumberOfVertices = ((yMax - yMin)*(xMax - xMin));

    std::cout << "Vertices: " << mNumberOfVertices << std::endl;

    Vec3 position;

    mVertices = new Vertex[mNumberOfVertices];
    for(int i = 0; i < (yMax - yMin); i++)
    {
        for(int j = 0; j < (xMax - xMin); j++)
        {
            position = Vec3((i + xMin) * interval, function(i + xMin, j + yMin), (j + yMin) * interval);

            mVertices[i*(xMax - xMin) + j] = Vertex(position, Vec3(0.7f, 0.7f, 0.7f), Vec2(0.f, 0.f));
        }
    }

    std::vector<Vec3> normals = getSurfaceNormals();

    for(int i = 0; i < (yMax - yMin); i++)
    {
        for(int j = 0; j < (xMax - xMin); j++)
        {
            mVertices[i*(xMax - xMin) + j].set_normal(normals[i*(xMax - xMin) + j]);
        }
    }

    std::vector<int> indexVector;
    for(int j = 0; j < ((yMax - yMin - 1)); j++)
    {
        for(int i = 0; i < ((xMax - xMin - 1)); i++)
        {
            indexVector.push_back(i + j*((yMax-yMin)));
            indexVector.push_back((i+1) + j*((yMax-yMin)));
            indexVector.push_back((i) + (j+1)*((yMax-yMin)));

            indexVector.push_back((i) + (j+1)*((yMax-yMin)));
            indexVector.push_back((i+1) + j*((yMax-yMin)));
            indexVector.push_back((i+1) + (j+1)*((yMax-yMin)));
        }
    }


    unsigned int indices[indexVector.size()];

    for(unsigned int i = 0; i < indexVector.size(); i++)
    {
        indices[i] = indexVector[i];
    }

    writeToFile((gsl::valuesFilePath + "indices.txt").c_str(), indices, indexVector.size());
    populateTrinangleStruct("triangles.txt");

    //Set up the OpenGL part:
    initializeOpenGLFunctions();

    glGenVertexArrays( 1, &mVAO);

    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices
    glGenBuffers( 1, &mBufferObject );
    glBindBuffer( GL_ARRAY_BUFFER, mBufferObject );
    glBufferData( GL_ARRAY_BUFFER, mNumberOfVertices * sizeof( GLfloat ) * sizeof(Vertex),
                  mVertices, GL_STATIC_DRAW );  // 8 floats pr vertex

    //Element Buffer Object
    glGenBuffers(1, &mElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void surface3D::drawObject()
{

}

float surface3D::function(float x, float y)
{
    return (sin(x) + cos(y));
}

std::vector<Vec3> surface3D::getSurfaceNormals()
{
    Vec3 p0, p1, p2;

    std::vector<Vec3> normals;

    // df/dx = cos(x), df/dy = -sin(x) for f(x,y) = sin(x) + cos(y)

    for(int i = 0; i < (yMax - yMin); i++)
    {
        for(int j = 0; j < (xMax - xMin); j++)
        {
            p0 = Vec3(0, 0, function(i + yMin, j + xMin) + (j - (cos(j + xMin))) + (i + sin(i + yMin)));
            p1 = Vec3(1.f, 0.f, function(i + yMin, j + 1 + xMin) + (j + 1 - (cos(j + 1 + xMin))) + (i + sin(i + yMin)));
            p2 = Vec3(0.f, 1.f, function(i + 1 + yMin, j + xMin) + (j - (cos(j + xMin))) + (i + 1 + sin(i+ 1 + yMin)));

            Vec3 u = p1 - p0;
            Vec3 v = p2 - p0;

            Vec3 n = u ^ v;

            n.normalize();

            n = Vec3(fabs(n.getX()), fabs(n.getY()), fabs(n.getZ()));

            normals.push_back(n);

        }
    }
    return normals;
}

void surface3D::writeToFile(std::string fileName, unsigned int indices[], int arrayLength)
{
    std::ofstream indexFile;

    indexFile.open(fileName);

    for(int i = 0; i < arrayLength; i++)
    {
        if(i % 3 == 0)
        {
            indexFile << std::endl;
        }

        indexFile << indices[i] << " ";
    }
    indexFile.close();
}

int surface3D::getNumberofIndices()
{
    return mNumberOfIndices;
}

void surface3D::populateTrinangleStruct(std::string fileName)
{
    std::string filePath = gsl::valuesFilePath + fileName;
    std::ifstream inData(filePath.c_str());

    int positions[3];
    int neighbors[3];

    while(!inData.eof())
    {
        inData >> positions[0] >> positions[1] >> positions [2]
                >> neighbors[0] >> neighbors[1] >> neighbors[2];

        Triangles.push_back(TriangleS(positions, neighbors));
    }

}

int surface3D::findTriangle(int p, Vec3 q, std::vector<Vec3> &bezierValues)
{

    /* Vec3 bCoords = q.barycentricCoordinates(mVertices[currentTriangle.nodes[0]].get_xyz(),
                                             mVertices[currentTriangle.nodes[1]].get_xyz(),
                                             mVertices[currentTriangle.nodes[2]].get_xyz());*/
    if(p == -1)
    {
        return p;
    }

    TriangleS currentTriangle = Triangles[p];

    float bc[3];
    Vec3 x[2];
    x[0] = mVertices[currentTriangle.nodes[1]].get_xyz() - mVertices[currentTriangle.nodes[0]].get_xyz();
    x[1] = mVertices[currentTriangle.nodes[2]].get_xyz() - mVertices[currentTriangle.nodes[0]].get_xyz();
    float xAreal{Vec3(x[0] ^ x[1]).length()};
    for(int i{0}; i < 3; i++)
    {
        Vec3 varible1{mVertices[currentTriangle.nodes[(i+1)%3]].get_xyz() - q};
        Vec3 varible2{mVertices[currentTriangle.nodes[(i+2)%3]].get_xyz() - q};
        float qAreal{Vec3(varible1 ^ varible2).getY()/xAreal};
        bc[i] = qAreal;
    }

    if(bc[0] >= 0 && bc[1] >= 0 && bc[2] >= 0)
    {
        bezierValues.push_back(q);
        return p;
    }

    bezierValues.push_back(mVertices[currentTriangle.nodes[0]].get_xyz());
    return findTriangle(p + 1, q, bezierValues);


    /*if(bc[0] < bc[1] && bc[0] < bc[2])
    {
        bezierValues.push_back(mVertices[currentTriangle.nodes[0]].get_xyz());
        return findTriangle(currentTriangle.neighbors[0], q, bezierValues);
    }

    if(bc[1] < bc[0] && bc[1] < bc[2])
    {
        bezierValues.push_back(mVertices[currentTriangle.nodes[1]].get_xyz());
        return findTriangle(currentTriangle.neighbors[1], q, bezierValues);
    }

    if(bc[2] < bc[0] && bc[2] < bc[1])
    {
        bezierValues.push_back(mVertices[currentTriangle.nodes[2]].get_xyz());
        return findTriangle(currentTriangle.neighbors[2], q, bezierValues);
    }*/

}
