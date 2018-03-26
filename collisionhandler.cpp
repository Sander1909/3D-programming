#include "collisionhandler.h"
#include "sceneobject.h"
/*
collisionHandler::collisionHandler(SceneObject *owner)
{
    mOwner = owner;
}

bool collisionHandler::isColliding(std::unique_ptr<SceneObject> o1)
{
    if(mOwner->getTransform()->getPosition().getZ() > 6.f || mOwner->getTransform()->getPosition().getZ() < -6.f) //collide in z wall
    {
        std::cout << "hit z wall!" <<std::endl;
        return true;
    }
    if(mOwner->getTransform()->getPosition().getX() > 6.f || mOwner->getTransform()->getPosition().getX() < -6.f) //collide in x wall
    {
        std::cout << "hit x wall!" <<std::endl;
        return true;
    }

    if(Vec3(mOwner->getTransform()->getPosition() - o1->getTransform()->getPosition()).length() < 2.f) //collide in ball
    {
        std::cout << "hit ball!" <<std::endl;
        return true;
    }
    return false;
}
*/
