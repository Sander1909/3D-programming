#include "transform.h"
#include "sceneobject.h"
#include "vec3.h"

Transform::Transform(SceneObject* owner) : mLocalScale{1.f, 1.f, 1.f}
{
    mSceneObject = owner;
}

Vec3 Transform::getPosition()
{
    if (mSceneObject->getParent())    //for a hierarky of scene objects
    {
        Vec3 parentPos = mSceneObject->getParent()->getTransform()->getPosition();
        return mLocalPosition + parentPos;
    }

    return mLocalPosition;
}

Vec3 Transform::getRotation()
{
    if (mSceneObject->getParent())
    {
        Vec3 parentRot = mSceneObject->getParent()->getTransform()->getRotation();
        return mLocalRotation + parentRot;
    }

    return mLocalRotation;
}

Vec3 Transform::getScale()
{
    if (mSceneObject->getParent() != nullptr)
    {
        Vec3 parentScale = mSceneObject->getParent()->getTransform()->getScale();
        return mLocalScale + parentScale;
    }

    return mLocalScale;
}

void Transform::setPosition(float x, float y, float z)
{
    mLocalPosition = Vec3(x, y, z);
}

void Transform::setPosition(Vec3 pos) { mLocalPosition = pos; }

void Transform::setRotation(float x, float y, float z)
{
    mLocalRotation = Vec3(x, y, z);
}

void Transform::setRotation(Vec3 rot) { mLocalRotation = rot; }

void Transform::setScale(float x, float y, float z)
{
    mLocalScale = Vec3(x, y, z);
}

void Transform::setScale(Vec3 scale) { mLocalScale = scale; }

void Transform::translate(float x, float y, float z)
{
    mLocalPosition = mLocalPosition + Vec3(x, y, z);
}

void Transform::translate(Vec3 vecIn)
{
    mLocalPosition = mLocalPosition + vecIn;
}

void Transform::rotate(float x, float y, float z)
{
    mLocalRotation = mLocalRotation + Vec3(x, y, z);
}
