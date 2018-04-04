#include "light.h"

Light::Light()
{

}

void Light::setColor(Vec3 inColor)
{
    mColor = inColor;
}

Vec3 Light::getColor()
{
    return mColor;
}

void Light::setStrength(float inStrength)
{
    mStrength = inStrength;
}

float Light::getStrength()
{
    return mStrength;
}
