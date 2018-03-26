#include "light.h"

Light::Light()
{

}

void Light::setColor(Vec3 inColor)
{
    color = inColor;
}

Vec3 Light::getColor()
{
    return color;
}
