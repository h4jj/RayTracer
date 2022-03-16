#pragma once
#include <vector> 
#include "Ray.h"
#include "Surface.h"
#include "Output.h"

class Light {

public:
    Eigen::Vector3f lightPosition, diffuseIntensity, specularIntensity;

    virtual ~Light() {};
    virtual void illuminate(Surface, Eigen::Vector3f&, Output, std::vector<Surface*>) {};
    virtual void globalIlluminate(Surface, Eigen::Vector3f&, Output, std::vector<Surface*>) {};
    virtual bool is_shadowed(const Surface s, const Light l, const std::vector<Surface*> surfaces) {

        Eigen::Vector3f shadow_vector = l.lightPosition - s.hrec.position;
        float distance = shadow_vector.norm();
        shadow_vector.normalize();
        Ray shadowRay(s.hrec.position, shadow_vector);

        for(const auto sItem : surfaces) {
            if(sItem->hrec.t != s.hrec.t) {
                if(sItem->hit(shadowRay)) {
                    if((sItem->hrec.position - s.hrec.position).norm() <= distance) {
                        if(sItem->hrec.t > 0) {
                            return true;
                        }
                    }
                }
            }        
        }
        
        return false;
    }

};