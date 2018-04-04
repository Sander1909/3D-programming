#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light.h"

class AmbientLight: public Light
{
public:
    AmbientLight(Vec3 inColor = Vec3(0.f, 0.f, 0.f), float inStrength = 0.f);
};

#endif // AMBIENTLIGHT_H
