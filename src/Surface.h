#pragma once

#include "HitRecord.h"
#include "Ray.h"

#include "BoundingBox.h"

struct Material {
    float pc, ka, kd, ks;
    Eigen::Vector3f ac, dc, sc;
};

class Surface {
public:
    HitRecord hrec;
    Material mat;
    BoundingBox *bbox;
    std::string type;
    virtual inline ~Surface() {};
    virtual bool hit(Ray&) {return true;};
    virtual bool hit_shadow(Ray) {return true;};
    
};