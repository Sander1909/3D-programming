#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "sceneobject.h"

class Vertex;
class Matrix4x4;

class Triangle : public SceneObject
{
public:
    Triangle();
    ~Triangle();

    void createObject() override;
    void drawObject() override;
};

#endif // TRIANGLE_H
