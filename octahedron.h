#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include <string>
#include "sceneobject.h"

class Vec3;

class Octahedron : public SceneObject
{
public:
    Octahedron(int n = 0);
    ~Octahedron();

    void createObject() override;
    void drawObject() override;

    void setYPosition(float yPos);

private:
    void makeTriangle(const Vec3& v1, const Vec3& v2, const Vec3& v3);
    void subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n);
    void makeUnitOctahedron();

    int mRecursions;          //
    int mIndex;               // brukes i rekursjon, til å bygge m_vertices

};

#endif // OCTAHEDRON_H
