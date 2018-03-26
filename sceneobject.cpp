#include "sceneobject.h"
#include "vertex.h"
#include "transform.h"
#include <QMatrix4x4>

SceneObject::SceneObject() : mParent{nullptr}//, mCollision{new collisionHandler(this)}
{
    mTransform = std::shared_ptr<Transform>(new Transform(this));
    mModelMatrix = std::unique_ptr<QMatrix4x4>(new QMatrix4x4);
    mModelMatrix->setToIdentity();
}

SceneObject::~SceneObject()
{
    //std::cout << "SceneObject deleted\n";
}

Vertex *SceneObject::vertices() const
{
    return mVertices;
}

std::shared_ptr<SceneObject> SceneObject::getParent() const
{
    return mParent;
}

void SceneObject::setParent(const std::shared_ptr<SceneObject> &parent)
{
    mParent = parent;
}

std::shared_ptr<Transform> SceneObject::getTransform() const
{
    return mTransform;
}

std::shared_ptr<QMatrix4x4> SceneObject::getModelMatrix() const
{
    mModelMatrix->setToIdentity();
    mModelMatrix->translate(mTransform->getPosition().getX(), mTransform->getPosition().getY(), mTransform->getPosition().getZ());
    mModelMatrix->rotate(mTransform->getRotation().getX(), 1.0f, 0.f, 0.f);
    mModelMatrix->rotate(mTransform->getRotation().getY(), 0.f, 1.0f, 0.f);
    mModelMatrix->rotate(mTransform->getRotation().getZ(), 0.f, 0.f, 1.0f);
    mModelMatrix->scale(mTransform->getScale().getX(), mTransform->getScale().getY(), mTransform->getScale().getZ());

    return mModelMatrix;
}

void SceneObject::setVelocity(Vec3 inVel)
{
    vel = inVel;
}

Vec3 SceneObject::getVelocity()
{
    return vel;
}

void SceneObject::setForce(Vec3 inForce)
{
    force = inForce;
}

Vec3 SceneObject::getForce()
{
    return force;
}

void SceneObject::setAcceleration(Vec3 inAcc)
{
    acc = inAcc;
}

Vec3 SceneObject::getAcceleration()
{
    return acc;
}

void SceneObject::setMass(float inMass)
{
    mass = inMass;
}

float SceneObject::getMass()
{
    return mass;
}

void SceneObject::setVelX(float f)
{
    vel.setX(f);
}

void SceneObject::setVelY(float f)
{
    vel.setY(f);
}

void SceneObject::setVelZ(float f)
{
    vel.setZ(f);
}

void SceneObject::applyForces(float deltaTime)
{
    acc = force / mass;
    vel = vel + (acc * deltaTime);
    getTransform()->setPosition(getTransform()->getPosition() + (vel * deltaTime));

    vel = vel * 0.99f;
    setForce(getForce() * 0);
    if(vel.length() < 0.0001)
    {
        vel = vel * 0;
    }
}

void SceneObject::wallCollision()
{
    if(getTransform()->getPosition().getZ() > 6.f || getTransform()->getPosition().getZ() < -6.f) //collide in z wall
    {
        if(getTransform()->getPosition().getZ() > 6.f)
        {
            getTransform()->setPosition(getTransform()->getPosition().getX(), getTransform()->getPosition().getY(), 5.9f);
        }
        else if(getTransform()->getPosition().getZ() < -6.f)
        {
            getTransform()->setPosition(getTransform()->getPosition().getX(), getTransform()->getPosition().getY(), -5.9f);
        }
        setVelZ(getVelocity().getZ() * -1);
    }
    if(getTransform()->getPosition().getX() > 6.f || getTransform()->getPosition().getX() < -6.f) //collide in x wall
    {
        if(getTransform()->getPosition().getX() > 6.f)
        {
            getTransform()->setPosition(5.9f, getTransform()->getPosition().getY(), getTransform()->getPosition().getZ());
        }
        else if(getTransform()->getPosition().getX() < -6.f)
        {
            getTransform()->setPosition(-5.9f, getTransform()->getPosition().getY(), getTransform()->getPosition().getZ());
        }
        setVelX(getVelocity().getX() * -1);
    }
}

/*collisionHandler* SceneObject::getCollisionHandler() const
{
    return mCollision;
}
*/
