#pragma once

#include "Surface.h"

class Rectangle : public Surface {
public:
    Eigen::Vector3f p1,p2,p3,p4;
    std::string comment;
    virtual ~Rectangle() {};
    
    // bool hit_triangle(Ray& r, const Eigen::Vector3f& a,const Eigen::Vector3f& b,const Eigen::Vector3f& c) {
        
    //     Eigen::Matrix3f Amatrix, tMatrix, betaMatrix, gammaMatrix;
    //     float t,Beta,Gamma;

    //     Amatrix << (a.x() - b.x()), (a.x() - c.x()), r.direction.x(), (a.y() - b.y()), (a.y() - c.y()), r.direction.y(), (a.z() - b.z()), (a.z() - c.z()), r.direction.z();
    //     float detA = Amatrix.determinant();
        
    //     tMatrix << (a.x() - b.x()), (a.x() - c.x()), (a.x() - r.origin.x()), (a.y() - b.y()), (a.y() - c.y()), (a.y() - r.origin.y()), (a.z() - b.z()), (a.z() - c.z()), (a.z() - r.origin.z());
    //     betaMatrix << (a.x() - r.origin.x()), (a.x() - c.x()), r.direction.x(), (a.y() - r.origin.y()), (a.y() - c.y()), r.direction.y(), (a.z() - r.origin.z()), (a.z() - c.z()), r.direction.z();
    //     gammaMatrix << (a.x() - b.x()), (a.x() - r.origin.x()), r.direction.x(), (a.y() - b.y()), (a.y() - r.origin.y()), r.direction.y(), (a.z() - b.z()), (a.z() - r.origin.z()), r.direction.z();

    //     t = tMatrix.determinant() / detA;

    //     if(t < 0) {
    //         return false;
    //     }

    //     Gamma = gammaMatrix.determinant() / detA;

    //     if(Gamma < 0 || Gamma > 1) {
    //         return false;
    //     }

    //     Beta = betaMatrix.determinant() / detA;

    //     if(Beta < 0 || Beta > 1 - Gamma) {
    //         return false;
    //     }

    //     this->hrec.t = t;
    //     this->hrec.position = r.Location(this->hrec.t);
    //     this->hrec.normal = (b-a).cross(c-a);
        
    //     return true;
    // };
    
    // virtual bool hit(Ray& r) {

    //     auto t1 = hit_triangle(r, p1, p2, p3);
    //     auto t2 = hit_triangle(r, p4, p1, p3);

    //     if(t1 || t2) return true;
    //     return false;
    // };
    
    virtual bool hit(Ray& r) {

        float t = -(hrec.normal.x()*(r.origin.x() - p1.x()) + hrec.normal.y()*(r.origin.y() - p1.y()) + hrec.normal.z()*(r.origin.z() - p1.z())) / (hrec.normal.x()*r.direction.x() + hrec.normal.y()*r.direction.y() + hrec.normal.z()*r.direction.z());
        Eigen::Vector3f location = r.Location(t);
        Eigen::Vector3f AM = r.Location(t) - p1;
        Eigen::Vector3f AB = p4 - p1;
        Eigen::Vector3f AD = p2 - p1;

        if(AM.dot(AB) > 0 && AB.dot(AB) > AM.dot(AB)) {
            if(AM.dot(AD) > 0 && AD.dot(AD) > AM.dot(AD)) {
                this->hrec.t = t;
                this->hrec.position = location;
                return true;
            }
        }
        

        return false;
    };
};