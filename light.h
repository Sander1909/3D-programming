#ifndef LIGHT_H
#define LIGHT_H

#include <sceneobject.h>

class Light: public SceneObject
{
protected:

    Vec3 mColor;
    float mStrength;

public:
    Light();

    void setColor(Vec3 inColor);
    Vec3 getColor();

    void setStrength(float inStrength);
    float getStrength();
};

#endif // LIGHT_H
