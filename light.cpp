#include "light.h"

Light::Light(Vec3 inColor, float inStrength, Vec3 inPosition)
{
    mColor = inColor;
    mStrength = inStrength;
    getTransform()->setPosition(inPosition);

    mMesh = new Octahedron(2, Vec3(1.f, 1.f, 0.5f));
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

Octahedron *Light::getMesh()
{
    return mMesh;
}

void Light::createObject()
{

}

void Light::drawObject()
{

}
