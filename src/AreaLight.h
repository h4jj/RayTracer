#pragma once

#include "Light.h"

class AreaLight : public Light {

public:
    Eigen::Vector3f p1,p2,p3,p4,normal;
    const int grid = 4;
    virtual ~AreaLight() {};
    virtual void globalIlluminate(Surface, Eigen::Vector3f&, Output, std::vector<Surface*>) {};
    virtual void illuminate(Surface sur, Eigen::Vector3f& finalColor, Output o, std::vector<Surface*> surfaces) {

        Eigen::Vector3f initialPoint = p1;
        Eigen::Vector3f horizontal = ( p4 - p1 ) / grid;
        Eigen::Vector3f vertical = (p2 - p1) / grid;
        Eigen::Vector3f diffuseColor(0,0,0), specularColor(0,0,0);
        Eigen::Vector3f midPixel = horizontal/2.0 + vertical/2.0;
        initialPoint += midPixel;
        this->lightPosition = initialPoint;

        for(int i{0}; i<grid; i++) {
            for(int j{0}; j<grid; j++) {
                this->lightPosition = initialPoint;

                if(is_shadowed(sur, *this, surfaces)) { 
                    initialPoint += horizontal;
                    continue;
                }
                Eigen::Vector3f lightVector = this->lightPosition - sur.hrec.position;
                Eigen::Vector3f ViewingVector = o.camera - sur.hrec.position;

                ViewingVector.normalize();
                lightVector.normalize();
                
                Eigen::Vector3f halfVector = lightVector + ViewingVector;
                
                
                halfVector.normalize();
                sur.hrec.normal.normalize();

                float costheta = sur.hrec.normal.dot(lightVector);
                float beta = pow(halfVector.dot(sur.hrec.normal), sur.mat.pc);
                
                if(costheta > 0) {
                    diffuseColor = sur.mat.kd * this->diffuseIntensity.cwiseProduct(sur.mat.dc) * costheta;
                }

                if(beta > 0) {
                    specularColor = sur.mat.ks * this->specularIntensity.cwiseProduct(sur.mat.sc) * beta;
                }

                finalColor += diffuseColor + specularColor;
    
                initialPoint += horizontal;
                // std::cout << "initialPoint: " << initialPoint << std::endl;
            }
            initialPoint -= horizontal*grid;
            initialPoint += vertical;
        }
        // std::cout << "initialPoint: " << initialPoint << std::endl;
        // exit(0);
        // std::cout << "Final Color before: " << finalColor << std::endl;
        finalColor /= grid*grid;
        // std::cout << "Final Color after: " << finalColor << std::endl;
        // exit(0);
    }; 
};