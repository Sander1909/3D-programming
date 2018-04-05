#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "light.h"

class DiffuseLight: public Light
{
public:
    DiffuseLight(Vec3 inColor, float inStrength, Vec3 inPos);

    void createObject() override;
    void drawObject() override;
};

#endif // DIFFUSELIGHT_H
