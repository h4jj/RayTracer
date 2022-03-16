#include "Sphere.h"

bool Sphere::hit(Ray& r) {
    
    r.direction.normalize();
    float t = (this->center - r.origin).dot(r.direction);
    Eigen::Vector3f p = r.Location(t);
    float y = (this->center - p).norm();  

    if(y < this->radius) {
        
        float x = sqrt(this->radius*this->radius - y*y);
        float t1 = t-x;
        float t2 = t+x;

        if(t1 < t2) {
            
            this->hrec.t = t1;

            this->hrec.position = r.Location(this->hrec.t);
            this->hrec.normal = this->hrec.position - this->center;
  
            return true;
        }
        
        this->hrec.t = t2;

        this->hrec.position = r.Location(this->hrec.t);
        this->hrec.normal = this->hrec.position - this->center;
        
        return true;
        
    }
    return false;
}