#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

//#include <QMatrix4x4>   //must be included for unique_ptr sizeof to work
#include <QOpenGLFunctions_4_1_Core>
#include <memory>
#include <vec3.h>
#include "collisionhandler.h"

class Vertex;
class Matrix4x4;
class Transform;
class QMatrix4x4;
class QOpenGLContext;
//class collisionHandler;

class SceneObject : protected QOpenGLFunctions_4_1_Core
{
public:
    SceneObject();
    ~SceneObject();

    int mNumberOfVertices;

    Vertex *vertices() const;

    virtual void createObject() = 0;
    virtual void drawObject() = 0;

    std::shared_ptr<SceneObject> getParent() const;
    void setParent(const std::shared_ptr<SceneObject> &parent);

    std::shared_ptr<Transform> getTransform() const;
    std::shared_ptr<QMatrix4x4> getModelMatrix() const;

    GLuint mVAO{0};    //the Vertex Array Object for this object

    //Physics----------------------------
    void setVelocity(Vec3 inVel);
    Vec3 getVelocity();
    void setForce(Vec3 inForce);
    Vec3 getForce();
    void setAcceleration(Vec3 inAcc);
    Vec3 getAcceleration();
    void setMass(float inMass);
    float getMass();

    void setVelX(float f);
    void setVelY(float f);
    void setVelZ(float f);

    void applyForces(float deltaTime); //for render-loop
    void wallCollision();              //for render-loop
    //-----------------------------------

    //collisionHandler *getCollisionHandler() const;

protected:
    Vertex* mVertices;
    std::shared_ptr<SceneObject> mParent;
    std::shared_ptr<Transform> mTransform;
    std::shared_ptr<QMatrix4x4> mModelMatrix;

    GLuint mBufferObject;   //the Vertex Buffer Object for this object

    //collisionHandler* mCollision;

private:
    //Physics
    Vec3 vel;
    Vec3 force;
    Vec3 acc;
    float mass;
    //-------
};

#endif // SCENEOBJECT_H
