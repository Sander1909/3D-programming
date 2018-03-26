#ifndef AXIS_H
#define AXIS_H

#include <QtGui/qopengl.h> // for GLfloat
#include "sceneobject.h"

class Vertex;
class Matrix4x4;

class Axis : public SceneObject
{
public:
    Axis();
    ~Axis();

    void createObject() override;
    void drawObject() override;
};

#endif // AXIS_H
