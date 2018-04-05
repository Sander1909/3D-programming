#include "diffuselight.h"

DiffuseLight::DiffuseLight(Vec3 inColor, float inStrength, Vec3 inPos)
{
    mColor = inColor;
    mStrength = inStrength;
    getTransform()->setPosition(inPos);
}

void DiffuseLight::createObject()
{

}

void DiffuseLight::drawObject()
{

}
