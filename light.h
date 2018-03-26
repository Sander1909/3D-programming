#ifndef LIGHT_H
#define LIGHT_H

#include <sceneobject.h>

class Light: public SceneObject
{
private:

    Vec3 color;

public:
    Light();

    void setColor(Vec3 inColor);
    Vec3 getColor();
};

#endif // LIGHT_H
