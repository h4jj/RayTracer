#pragma once

#include "Ray.h"

struct Output {
    std::string filename;
    int fov, size[2], maxbounces;
    Eigen::Vector3f lookat, camera, up, left, ai, bkc;
    unsigned int speedup, raysperpixel[2];
    bool antialiasing, globalillum, twosiderender;
    float probterminate;
};