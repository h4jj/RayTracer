#pragma once

#include "Surface.h"

class Sphere : public Surface {
public:
    Eigen::Vector3f center;
    float radius;

    virtual ~Sphere() {};
    virtual bool hit(Ray& r);
};

