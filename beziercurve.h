#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H
#include "vec3.h"
#include "sceneobject.h"
#include "vertex.h"
#include <iostream>
#include <fstream>
#include <vector>

class BezierCurve : public SceneObject
{
protected:
    Vec3 b[4];
public:
    BezierCurve(std::string fileName);
    BezierCurve(std::vector<Vec3> v);

    Vec3 evaluateBezier(int degree, float t, Vec3 inC[4]);
    std::vector<Vec3> createCurvePoints();

    void createObject() override;
    void drawObject() override;
};

#endif // BEZIERCURVE_H
