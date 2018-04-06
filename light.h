#ifndef LIGHT_H
#define LIGHT_H

#include <sceneobject.h>
#include "octahedron.h"

class Light: public SceneObject
{
protected:

    Vec3 mColor;
    float mStrength;

    Octahedron *mMesh;

public:
    Light(Vec3 inColor = Vec3(0.f, 0.f, 0.f), float inStrength = 0.f, Vec3 inPosition = Vec3(0.f, 0.f, 0.f));

    void setColor(Vec3 inColor);
    Vec3 getColor();

    void setStrength(float inStrength);
    float getStrength();

    Octahedron* getMesh();

    virtual void createObject() override;
    virtual void drawObject() override;
};

#endif // LIGHT_H
