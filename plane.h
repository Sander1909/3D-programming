#ifndef PLANE_H
#define PLANE_H

#include <sceneobject.h>
#include "vertex.h"
#include "vec3.h"
#include "matrix4x4.h"
#include <QMatrix4x4>


class Vertex;
class Matrix4x4;

class Plane : public SceneObject
{
public:
    Plane();
    ~Plane();

    void createObject() override;
    void drawObject() override;
};

#endif // PLANE_H
