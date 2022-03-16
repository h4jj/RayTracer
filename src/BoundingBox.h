#pragma once

class BoundingBox {
public:
    ~BoundingBox() {}
    void construct() {} 
public:
    Eigen::Vector3f min, max;
};