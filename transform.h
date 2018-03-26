#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec3.h"

class SceneObject;

class Transform
{
public:
    Transform(SceneObject *owner);
    Vec3 getPosition();
    Vec3 getRotation();
    Vec3 getScale();

    void setPosition(float x, float y, float z);
    void setPosition(Vec3 pos);

    void setRotation(float x, float y, float z);
    void setRotation(Vec3 rot);

    void setScale(float x, float y, float z);
    void setScale(Vec3 scale);

    void translate(float x, float y, float z);
    void translate(Vec3 vecIn);
    void rotate(float x, float y, float z);

private:
    SceneObject* mSceneObject;   //a pointer to the owner of the transform

    Vec3 mLocalPosition;
    Vec3 mLocalRotation;
    Vec3 mLocalScale;
};

#endif // TRANSFORM_H
