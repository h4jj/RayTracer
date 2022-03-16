#pragma once
#include <Eigen/Core>


class HitRecord {
public:
    float t;
    Eigen::Vector3f normal, position;
};