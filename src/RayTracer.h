#pragma once
#include <iostream>
#include <math.h>
#include <random>
#include <queue>
#include <thread>
#include "../external/json.hpp"
#include "../external/simpleppm.h"
#include "Ray.h"
#include "HitRecord.h"
#include "BoundingBox.h"
#include "Surface.h"
#include "Sphere.h"
#include "Rectangle.h"
#include "Light.h"
#include "PointLight.h"
#include "AreaLight.h"
#include "Output.h"

class RayTracer {

    public:
        RayTracer(nlohmann::json& _j);
        void run();
        void extractSceneFromJSON();
        void extractGeometry();
        void extractLight();
        void extractOutput();
        void drawScene();
        void constructBoundingVolume();
        void drawSceneAntiAliasing();
        void drawSceneGlobalIllumination();
        void printBoundingVolumes();
        // bool is_shadowed(const Surface, const Light);
        Eigen::Vector3f rayColorGlobalIllumination(Ray, Output*, Eigen::Vector3f&, int);
        Eigen::Vector3f rayColor(Ray, Output*);

    private:
        nlohmann::json j;
        std::vector<Surface*> s;
        std::vector<Light*> l;
        std::vector<Output*> o;
};
