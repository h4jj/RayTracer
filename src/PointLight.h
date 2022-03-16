#pragma once

#include "Light.h"

class PointLight : public Light{

public:

    virtual ~PointLight() {};
    virtual void illuminate(Surface sur, Eigen::Vector3f& finalColor, Output o, std::vector<Surface*> surfaces) {

        if(is_shadowed(sur, *this, surfaces)) return;

        // ambient + diffuse + specular
        Eigen::Vector3f diffuseColor(0,0,0), specularColor(0,0,0);  

        Eigen::Vector3f lightVector = this->lightPosition - sur.hrec.position;

        // viewing ray - cam minus pos
        Eigen::Vector3f ViewingVector = o.camera - sur.hrec.position;
        
        ViewingVector.normalize();
        lightVector.normalize();

        // // test for shadow
        // Eigen::Vector3f shadowVector = lightVector;
        // Ray shadowRay(sur.hrec.position, shadowVector);

        Eigen::Vector3f halfVector = lightVector + ViewingVector;
        halfVector.normalize();
        
        sur.hrec.normal.normalize();

        
        float costheta = sur.hrec.normal.dot(lightVector);
        float beta = pow(halfVector.dot(sur.hrec.normal), sur.mat.pc);
        
        // NOTE: ANY ISSUES OCCUR IN THE FUTURE CHECK FOR NOMALIZATION ALWAYS
        // FIRST


        if(costheta > 0) {
            diffuseColor = sur.mat.kd * this->diffuseIntensity.cwiseProduct(sur.mat.dc) * costheta;
        }
         
        if(beta > 0) {
            specularColor = sur.mat.ks * this->specularIntensity.cwiseProduct(sur.mat.sc) * beta;
        }

        finalColor += diffuseColor + specularColor;
    };

    virtual void globalIlluminate(Surface sur, Eigen::Vector3f& finalColor, Output o, std::vector<Surface*> surfaces) {

        if(is_shadowed(sur, *this, surfaces)) return;

        // ambient + diffuse + specular
        Eigen::Vector3f diffuseColor(0,0,0);
        Eigen::Vector3f lightVector = this->lightPosition - sur.hrec.position;

        lightVector.normalize();
        sur.hrec.normal.normalize();

        float costheta = sur.hrec.normal.dot(lightVector);
        
        // NOTE: ANY ISSUES OCCUR IN THE FUTURE CHECK FOR NOMALIZATION ALWAYS
        // FIRST


        if(costheta > 0) {
            diffuseColor = sur.mat.kd * this->diffuseIntensity.cwiseProduct(sur.mat.dc) * costheta;
        }
         
        finalColor += diffuseColor;
    };


};