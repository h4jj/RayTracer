#ifndef RAY_H
#define RAY_H

#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>

class Ray {
    public:
        Ray() {}
        Ray(Eigen::Vector3f _origin, Eigen::Vector3f _direction) : origin(_origin), direction(_direction) {} 
        Eigen::Vector3f getOrigin() {return origin;}
        Eigen::Vector3f getDirection() {return direction;}
        Eigen::Vector3f Location(float t) {return origin + t*direction;}

    public:
        Eigen::Vector3f origin;
        Eigen::Vector3f direction;
        
};

#endif