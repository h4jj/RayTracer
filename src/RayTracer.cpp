#include "RayTracer.h"

using std::cout;
using std::endl;


RayTracer::RayTracer(nlohmann::json& _j) {
    j = _j;
}

void RayTracer::extractGeometry() {
    cout<<"Geometry: "<<endl;
    int gc = 0;
    
    // use iterators to read-in array types
    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++){
        
        std::string type;
        if(itr->contains("type")){
           // type = static_cast<std::string>((*itr)["type"]);
            type = (*itr)["type"].get<std::string>();
        } else {
            cout<<"Fatal error: geometry should always contain a type!!!"<<endl;
            return;
        }
        
        if(type=="sphere"){
            
            cout<<"Sphere: "<<endl;
            Sphere* sp = new Sphere();
            sp->type = type;

            int i = 0;
            for (auto itr2 =(*itr)["centre"].begin(); itr2!= (*itr)["centre"].end(); itr2++){
                if(i<3){
                    sp->center[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["ac"].begin(); itr2!= (*itr)["ac"].end(); itr2++){
                if(i<3){
                    sp->mat.ac[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
            i = 0;
            for (auto itr2 =(*itr)["dc"].begin(); itr2!= (*itr)["dc"].end(); itr2++){
                if(i<3){
                    sp->mat.dc[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
            i = 0;
            for (auto itr2 =(*itr)["sc"].begin(); itr2!= (*itr)["sc"].end(); itr2++){
                if(i<3){
                    sp->mat.sc[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            if(itr->contains("radius")) {
                float r = (*itr)["radius"].get<float>();
                sp->radius = r;
            }

            if(itr->contains("ka")) {
                float ka = (*itr)["ka"].get<float>();
                sp->mat.ka = ka;    
            }

            if(itr->contains("kd")) {
                float kd = (*itr)["kd"].get<float>();
                sp->mat.kd = kd;    
            }

            if(itr->contains("ks")) {
                float ks = (*itr)["ks"].get<float>();
                sp->mat.ks = ks;    
            }

            if(itr->contains("pc")) {
                float pc = (*itr)["pc"].get<float>();
                sp->mat.pc = pc;    
            }



            // cout<<"Centre: "<<sp->center<<endl;
            // cout<<"Radius: "<<sp->radius<<endl;
            // cout<<"ka: "<<sp->mat.ka<<endl;
            // cout<<"kd: "<<sp->mat.kd<<endl;
            // cout<<"ks: "<<sp->mat.ks<<endl;
            // cout<<"ac: "<<sp->mat.ac<<endl;
            // cout<<"dc: "<<sp->mat.dc<<endl;
            // cout<<"sc: "<<sp->mat.sc<<endl;
    
            this->s.push_back(sp);
        }
        else if(type=="rectangle") {
            cout<<"Rectangle: "<<endl;
            Rectangle* re = new Rectangle();
            re->type = type;

            if(itr->contains("comment")) {
                re->comment = (*itr)["comment"].get<std::string>();
            }

            int i = 0;
            for (auto itr2 =(*itr)["p1"].begin(); itr2!= (*itr)["p1"].end(); itr2++){
                if(i<3){
                    re->p1[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["p2"].begin(); itr2!= (*itr)["p2"].end(); itr2++){
                if(i<3){
                    re->p2[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["p3"].begin(); itr2!= (*itr)["p3"].end(); itr2++){
                if(i<3){
                    re->p3[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["p4"].begin(); itr2!= (*itr)["p4"].end(); itr2++){
                if(i<3){
                    re->p4[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["ac"].begin(); itr2!= (*itr)["ac"].end(); itr2++){
                if(i<3){
                    re->mat.ac[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
            i = 0;
            for (auto itr2 =(*itr)["dc"].begin(); itr2!= (*itr)["dc"].end(); itr2++){
                if(i<3){
                    re->mat.dc[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
            i = 0;
            for (auto itr2 =(*itr)["sc"].begin(); itr2!= (*itr)["sc"].end(); itr2++){
                if(i<3){
                    re->mat.sc[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            if(itr->contains("ka")) {
                float ka = (*itr)["ka"].get<float>();
                re->mat.ka = ka;    
            }

            if(itr->contains("kd")) {
                float kd = (*itr)["kd"].get<float>();
                re->mat.kd = kd;    
            }

            if(itr->contains("ks")) {
                float ks = (*itr)["ks"].get<float>();
                re->mat.ks = ks;    
            }

            if(itr->contains("pc")) {
                float pc = (*itr)["pc"].get<float>();
                re->mat.pc = pc;    
            }
            Eigen::Vector3f vertical = re->p2 - re->p1;
            Eigen::Vector3f horizontal = re->p4 - re->p1;
            
            // normal wasnt normalized before added these 4 lines

            vertical.normalize();
            horizontal.normalize();

            re->hrec.normal = vertical.cross(horizontal);
            
            this->s.push_back(re);
        }
        ++gc;
    }
    
    cout<<"We have: "<<gc<<" objects!"<<endl << endl;
    return;
}

void RayTracer::extractLight() {
    cout<<"Light: "<<endl;
    int gc = 0;
    
    // use iterators to read-in array types
    for (auto itr = j["light"].begin(); itr!= j["light"].end(); itr++){
        
        std::string type;
        if(itr->contains("type")){
           // type = static_cast<std::string>((*itr)["type"]);
            type = (*itr)["type"].get<std::string>();
        } else {
            cout<<"Fatal error: light should always contain a type!!!"<<endl;
            return;
        }
        
        if(type=="point"){
            
            cout<<"PointLight: "<<endl;
            PointLight* pl = new PointLight();

            int i = 0;
            for (auto itr2 =(*itr)["centre"].begin(); itr2!= (*itr)["centre"].end(); itr2++){
                if(i<3){
                    pl->lightPosition[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["id"].begin(); itr2!= (*itr)["id"].end(); itr2++){
                if(i<3){
                    pl->diffuseIntensity[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["is"].begin(); itr2!= (*itr)["is"].end(); itr2++){
                if(i<3){
                    pl->specularIntensity[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            cout << "Light position: " << pl->lightPosition << endl;
            cout << "diffuseIntensity: " << pl->diffuseIntensity << endl;
            cout << "specularIntensity: " << pl->specularIntensity << endl;

            this->l.push_back(pl);
        }
        else if(type=="area") {
            
            cout<<"area: "<<endl;
            Rectangle* re = new Rectangle();
            re->type = type;

            int i = 0;
            for (auto itr2 =(*itr)["p1"].begin(); itr2!= (*itr)["p1"].end(); itr2++){
                if(i<3){
                    re->p1[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["p2"].begin(); itr2!= (*itr)["p2"].end(); itr2++){
                if(i<3){
                    re->p2[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["p3"].begin(); itr2!= (*itr)["p3"].end(); itr2++){
                if(i<3){
                    re->p3[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["p4"].begin(); itr2!= (*itr)["p4"].end(); itr2++){
                if(i<3){
                    re->p4[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
            re->hrec.normal = (re->p2-re->p1).cross(re->p4-re->p1);
            // std::cout << "p1: " << re->p1 << std::endl;
            // std::cout << "p1: " << re->p2 << std::endl;
            // std::cout << "p1: " << re->p3 << std::endl;
            // std::cout << "p1: " << re->p4 << std::endl;
            // std::cout << "Type: " << re->type << std::endl;
            // this->s.push_back(re);

            if(itr->contains("usecenter")) {
                bool usecenter = (*itr)["usecenter"].get<bool>();
                
                // exit(0);
                if(usecenter == true) {
                    
                    cout << "point light: " << std::endl;

                    PointLight* pl = new PointLight();
                    pl->lightPosition = (re->p2 - re->p1)/2.0 + (re->p4 - re->p1)/2.0 + re->p1;
                    std::cout << "light position: " << pl->lightPosition << std::endl;
                    // exit(0);
                    i = 0;
                    for (auto itr2 =(*itr)["id"].begin(); itr2!= (*itr)["id"].end(); itr2++){
                        if(i<3){
                            pl->diffuseIntensity[i++] = (*itr2).get<float>();
                        } else {
                            cout<<"Warning: Too many entries in centre"<<endl;
                        }
                    }

                    i = 0;
                    for (auto itr2 =(*itr)["is"].begin(); itr2!= (*itr)["is"].end(); itr2++){
                        if(i<3){
                            pl->specularIntensity[i++] = (*itr2).get<float>();
                        } else {
                            cout<<"Warning: Too many entries in centre"<<endl;
                        }
                    }
                    this->l.push_back(pl);
                    // exit(0);
                    continue;
                }
            }

            AreaLight* al = new AreaLight();
            al->lightPosition = (re->p2 - re->p1)/2.0 + (re->p4 - re->p1)/2.0 + re->p1;
            al->p1 = re->p1;
            al->p2 = re->p2;
            al->p3 = re->p3;
            al->p4 = re->p4;
            al->normal = (re->p2-re->p1).cross(re->p4-re->p1);

            i = 0;
            for (auto itr2 =(*itr)["id"].begin(); itr2!= (*itr)["id"].end(); itr2++){
                if(i<3){
                    al->diffuseIntensity[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }

            i = 0;
            for (auto itr2 =(*itr)["is"].begin(); itr2!= (*itr)["is"].end(); itr2++){
                if(i<3){
                    al->specularIntensity[i++] = (*itr2).get<float>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
            
            this->l.push_back(al);


        }
        ++gc;
    }
    
    // exit(0);
    cout<<"We have: "<<gc<<" objects!"<<endl << endl;
    return;
}

void RayTracer::extractOutput() {
    cout<<"Output: "<<endl;
    
    // use iterators to read-in array types
    for (auto itr = j["output"].begin(); itr!= j["output"].end(); itr++){
        
        Output* op = new Output();
    
        op->filename = (*itr)["filename"].get<std::string>();
        op->fov = (*itr)["fov"].get<int>();

        int i = 0;
        for (auto itr2 =(*itr)["size"].begin(); itr2!= (*itr)["size"].end(); itr2++){
            if(i<2){
                op->size[i++] = (*itr2).get<int>();
            } else {
                cout<<"Warning: Too many entries in centre"<<endl;
            }
        }
        
        i = 0;
        for (auto itr2 =(*itr)["lookat"].begin(); itr2!= (*itr)["lookat"].end(); itr2++){
            if(i<3){
                op->lookat[i++] = (*itr2).get<float>();
            } else {
                cout<<"Warning: Too many entries in centre"<<endl;
            }
        }

        i = 0;
        for (auto itr2 =(*itr)["up"].begin(); itr2!= (*itr)["up"].end(); itr2++){
            if(i<3){
                op->up[i++] = (*itr2).get<float>();
            } else {
                cout<<"Warning: Too many entries in centre"<<endl;
            }
        }

        i = 0;
        for (auto itr2 =(*itr)["centre"].begin(); itr2!= (*itr)["centre"].end(); itr2++){
            if(i<3){
                op->camera[i++] = (*itr2).get<float>();
            } else {
                cout<<"Warning: Too many entries in centre"<<endl;
            }
        }

        i = 0;
        for (auto itr2 =(*itr)["ai"].begin(); itr2!= (*itr)["ai"].end(); itr2++){
            if(i<3){
                op->ai[i++] = (*itr2).get<float>();
            } else {
                cout<<"Warning: Too many entries in centre"<<endl;
            }
        }

        i = 0;
        for (auto itr2 =(*itr)["bkc"].begin(); itr2!= (*itr)["bkc"].end(); itr2++){
            if(i<3){
                op->bkc[i++] = (*itr2).get<float>();
            } else {
                cout<<"Warning: Too many entries in centre"<<endl;
            }
        }

        if(itr->contains("raysperpixel")) {
            i = 0;
            for (auto itr2 =(*itr)["raysperpixel"].begin(); itr2!= (*itr)["raysperpixel"].end(); itr2++){
                if(i<2){
                    op->raysperpixel[i++] = (*itr2).get<int>();
                } else {
                    cout<<"Warning: Too many entries in centre"<<endl;
                }
            }
        }

        if(itr->contains("antialiasing")) {
            op->antialiasing = (*itr)["antialiasing"].get<bool>();
        }

        if(itr->contains("globalillum")) {
            op->globalillum = (*itr)["globalillum"].get<bool>();
            op->maxbounces = (*itr)["maxbounces"].get<int>();
            op->probterminate = (*itr)["probterminate"].get<float>();
        }


        op->left = op->up.cross(op->lookat);
        this->o.push_back(op);

        // cout << "Camera: " << this->o->camera << endl;
        // cout << "Lookat: " << this->o->lookat << endl;
        // cout << "Up: " << this->o->up << endl;
        // cout << "Origin: " << this->o->origin << endl << endl;

    }

    return;
}

void RayTracer::extractSceneFromJSON() {
    extractGeometry();
    extractLight();
    extractOutput();
}


void computeBoundsForBox(Eigen::Vector3f obj, BoundingBox* bbox) {
    if(obj.x() < bbox->min.x()) {
        bbox->min.x() = obj.x();
    }
    
    if(obj.x() > bbox->max.x()) {
        bbox->max.x() = obj.x();
    }

    if(obj.y() < bbox->min.y()) {
        bbox->min.y() = obj.y();
    }
    
    if(obj.y() > bbox->max.y()) {
        bbox->max.y() = obj.y();
    }

    if(obj.z() < bbox->min.z()) {
        bbox->min.z() = obj.z();
    }
    
    if(obj.z() > bbox->max.z()) {
        bbox->max.z() = obj.z();
    }
}



void RayTracer::constructBoundingVolume() {
    for(const auto& obj : this->s) {
        BoundingBox* bbox = new BoundingBox();
        bbox->max = Eigen::Vector3f(-100000, -100000, -100000);
        bbox->min = Eigen::Vector3f(100000,100000,100000);
        if(obj->type == "rectangle") {
            computeBoundsForBox(static_cast<Rectangle*>(obj)->p1, bbox);
            computeBoundsForBox(static_cast<Rectangle*>(obj)->p2, bbox);
            computeBoundsForBox(static_cast<Rectangle*>(obj)->p3, bbox);
            computeBoundsForBox(static_cast<Rectangle*>(obj)->p4, bbox);

            obj->bbox = bbox;
        }
    }
}

void RayTracer::printBoundingVolumes() {
    for(const auto& obj : this->s) {
        std::cout << "bbox min: " << obj->bbox->min << std::endl;
        std::cout << "bbox max: " << obj->bbox->max << std::endl;
    }
}


// bool RayTracer::is_shadowed(const Surface s, const Light l) {
//     Eigen::Vector3f shadow_vector = l.lightPosition - s.hrec.position;
//     float distance = shadow_vector.norm();
//     shadow_vector.normalize();

//     Ray shadowRay(s.hrec.position, shadow_vector);

//     // loose checks here
//     // can check for t > 0 and norm < shadowVectorDistance to tighten up
    
//     for(const auto sItem : this->s) {
//         if(sItem->hrec.t != s.hrec.t) {
//             if(sItem->hit(shadowRay)) {
//                 if((sItem->hrec.position - s.hrec.position).norm() <= distance) {
//                     if(sItem->hrec.t > 0) return true;
//                 }
//             }
//         }        
//     }
//     // exit(0);
//     return false;
// }


Eigen::Vector3f RayTracer::rayColor(Ray _r, Output* o) {

    // compute sphere / rectangle / triangle intersection
    // implement comparator for priorityQ
    float t = 10000;
    Surface* sur = nullptr;

    for(auto &sItem : this->s) {
        if(sItem->hit(_r)) {
            if(sItem->hrec.t < t) {
                t = sItem->hrec.t;
                sur = sItem;
                
            }
        }
    }
    if(sur == nullptr) return o->bkc;

    Eigen::Vector3f finalColor(0,0,0);
  
    for(const auto lightItem : this->l) {
        if(lightItem->is_shadowed(*sur, *lightItem, this->s)) {continue;};
        lightItem->illuminate(*sur,finalColor, *o, this->s);
    }

    // exit(0); 

    // std::cout << "diffuse + specular: " << finalColor.x() << std::endl;
    finalColor.x() = sur->mat.ka * sur->mat.ac.x() + finalColor.x() > 1.0f ? 1.0f : sur->mat.ka * sur->mat.ac.x() + finalColor.x();
    finalColor.y() = sur->mat.ka * sur->mat.ac.y() + finalColor.y() > 1.0f ? 1.0f : sur->mat.ka * sur->mat.ac.y() + finalColor.y();
    finalColor.z() = sur->mat.ka * sur->mat.ac.z() + finalColor.z() > 1.0f ? 1.0f : sur->mat.ka * sur->mat.ac.z() + finalColor.z();
    // std::cout << "Final  Color: " << finalColor << std::endl;
    return finalColor;
}

void RayTracer::drawScene() {
    const double halfCircle = M_PI / 180;



    for(const auto& o : this->o) {
        const double fovOverTwoRadians = (o->fov / 2) * halfCircle;
        float delta = (2 * tan(fovOverTwoRadians)) / (float)(o->size[1]);
        Eigen::Vector3f upperLeftCorner = o->camera + o->lookat + (tan(fovOverTwoRadians) * o->up) + ((float)o->size[0]/2 * delta * o->left);
        std::vector<double> buffer(3*o->size[0] * o->size[1]); 
        // if(o->speedup == 1) {
        //     constructBoundingVolume();
        // }


        for(int j{0}; j<o->size[1] ; j++) {
            for(int i{0}; i<o->size[0]; i++) {
                Ray ray(o->camera, upperLeftCorner - (i*delta + delta/2)*o->left - (j*delta - delta/2)*o->up - o->camera);
                Eigen::Vector3f pixelColor = rayColor(ray, o);
                buffer[3*j*o->size[0]+3*i+0]=pixelColor.x();
                buffer[3*j*o->size[0]+3*i+1]=pixelColor.y();
                buffer[3*j*o->size[0]+3*i+2]=pixelColor.z();
            }
        }
        save_ppm(o->filename,buffer,o->size[0],o->size[1]);
    }
}

void RayTracer::drawSceneAntiAliasing() {
    const double halfCircle = M_PI / 180;
    bool bkc = false;

    for(const auto& o : this->o) {
        const double fovOverTwoRadians = (o->fov / 2) * halfCircle;
        float delta = (2 * tan(fovOverTwoRadians)) / (float)(o->size[1]);
        Eigen::Vector3f upperLeftCorner = o->camera + o->lookat + (tan(fovOverTwoRadians) * o->up) + ((float)o->size[0]/2 * delta * o->left);
        std::vector<double> buffer(3*o->size[0] * o->size[1]); 
        Eigen::Vector3f pixelColor(0,0,0);

        for(int j{0}; j<o->size[1] ; j++) {
            for(int i{0}; i<o->size[0]; i++) {
                pixelColor = Eigen::Vector3f(0,0,0);
                for(int k{0}; k < o->raysperpixel[0]; k++) {
                    bkc = false;
                    Ray ray(o->camera, upperLeftCorner - (i*delta + delta*k/10)*o->left - (j*delta - delta*k/10)*o->up - o->camera);
                    pixelColor += rayColor(ray, o);
                    if(pixelColor == o->bkc) {
                        
                        buffer[3*j*o->size[0]+3*i+0]=pixelColor.x();
                        buffer[3*j*o->size[0]+3*i+1]=pixelColor.y();
                        buffer[3*j*o->size[0]+3*i+2]=pixelColor.z();
                        bkc = true;
                        break;
                    }
                    
                }
                if(!bkc) {
                    pixelColor /= o->raysperpixel[0];
                    // std::cout << "pixelColor: " << pixelColor << std::endl;
                    // exit(0);
                    buffer[3*j*o->size[0]+3*i+0]=pixelColor.x();
                    buffer[3*j*o->size[0]+3*i+1]=pixelColor.y();
                    buffer[3*j*o->size[0]+3*i+2]=pixelColor.z();
                }
                
                
            }
        }
        save_ppm(o->filename,buffer,o->size[0],o->size[1]);
    }
}
Eigen::Vector3f RayTracer::rayColorGlobalIllumination(Ray _r, Output* o, Eigen::Vector3f& finalColor, int counter) {
    float t = 10000;
    Surface* sur = nullptr;

    // does this really need to be passed by reference? &sItem
    // could be causing some bugs

    // 1 hit object
    for(const auto& sItem : this->s) {
        Eigen::Vector3f positionBefore = sItem->hrec.position;
        if(sItem->hit(_r)) {
            if(positionBefore == sItem->hrec.position){
                continue;
            }
            else if(sItem->hrec.t < t) {
                if(sItem->hrec.t > 0){
                    t = sItem->hrec.t;
                    sur = sItem;
                }
            }
        }

    }

    if(sur == nullptr){
        if(counter > 0){
            // counter = 0;
            // std::cout <<"light ray escaped\n";
            return Eigen::Vector3f(-1,-1,-1);
        }
        
        return o->bkc;
    }
    // std::cout << "type: " << sur->type << std::endl;
    // if(sur->type == "rectangle") {
        // std::cout << "comment: " << dynamic_cast<Rectangle*>(sur)->comment << std::endl;
    // }
    // std::cout << "hitpoint position: " << sur->hrec.position << std::endl;
    // std::cout << "normal at hitpoint: " << sur->hrec.normal << std::endl;

    
    // 2 construct hemisphere and sample over it

    Eigen::Vector3f R(1,0,0),Z,X;
    if(R.dot(sur->hrec.normal) > 0.7 || R.dot(sur->hrec.normal) < -0.7) R = Eigen::Vector3f(0,1,0);
    // else if(R.dot(sur->hrec.normal) > 0.7) R = Eigen::Vector3f(0,1,0);

    if(R == Eigen::Vector3f(1,0,0)) {
        Z = R.cross(sur->hrec.normal);
        X = Z.cross(sur->hrec.normal);
    }
    else if(R == Eigen::Vector3f(0,1,0)) {
        X = R.cross(sur->hrec.normal);
        Z = X.cross(sur->hrec.normal);
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(-1, 1);
    std::uniform_real_distribution<> limitedDistr(0, 1);

    Eigen::Vector3f worldX(1, 0, 0);
    Eigen::Vector3f worldZ(0, 0, 1);
    Eigen::Vector3f worldNormal(0, 1, 0);

    Eigen::Vector3f samplePoint(distr(gen),0, distr(gen));
    samplePoint.y() = sqrt( 1 - pow(samplePoint.x(),2) + pow(samplePoint.z(),2));
    samplePoint.normalize();
    // std::cout << "samplePoint: " << samplePoint << std::endl;
    
    Eigen::Matrix<float,3,3> Rotation;
    Rotation << X.x(), sur->hrec.normal.x(), Z.x(),
                X.y(), sur->hrec.normal.y(), Z.y(),
                X.z(), sur->hrec.normal.z(), Z.z();
    
    Rotation.inverse();
    Eigen::Vector3f newPoint(Rotation(0,0)*samplePoint.x() + Rotation(0,1)*samplePoint.y() + Rotation(0,2)*samplePoint.z(),
                             Rotation(1,0)*samplePoint.x() + Rotation(1,1)*samplePoint.y() + Rotation(1,2)*samplePoint.z(),
                             Rotation(2,0)*samplePoint.x() + Rotation(2,1)*samplePoint.y() + Rotation(2,2)*samplePoint.z());

    newPoint.normalize();
    if(newPoint.dot(sur->hrec.normal) < 0) {
        newPoint = -newPoint;
    }
    
    float costheta = newPoint.dot(sur->hrec.normal);
    // new point correctly being generated
    Ray r(sur->hrec.position, newPoint);
    float randNum = limitedDistr(gen);
    counter++;
    // std::cout << "newpoint: " << newPoint << std::endl;
    if(randNum > o->probterminate && counter != o->maxbounces) {
        rayColorGlobalIllumination(r, o, finalColor, counter);
    }
    else {
        for(const auto light : this->l) {
            light->illuminate(*sur,finalColor,*o, this->s);
        }

        return finalColor;
    }
    finalColor += sur->mat.dc * sur->mat.kd * costheta;
    // std::cout << "final Color: " << finalColor << std::endl;

    return finalColor;
    // exit(0);

    
    // std::cout << "newPoint: " << newPoint << std::endl;

    // shoot ray and recurse
    // generate rand number; if number <= probterminate then sample light
    // if bounces = max bounces terminate and sample light
    // if recurse and escape dont count ray
    // while sampling light check for shadows as well

    // Ray bouncingRay(sur->hrec.position, newPoint);
    
    // srand(time(0));
    // float randNum = limitedDistr(gen);
    // float costheta = newPoint.dot(sur->hrec.normal);

    // if(randNum > o->probterminate || counter != o->maxbounces) {
    //     counter++;
    //     rayColorGlobalIllumination(bouncingRay, o, finalColor);
    // }
    // else {
    //     counter = 0;
    //     for(const auto light : this->l) {
    //         light->illuminate(*sur, finalColor, *o, this->s);
    //     }

    //     return finalColor;
    // }

    // finalColor += sur->mat.kd * sur->mat.dc * sur->hrec.normal.dot(newPoint);
    // // std::cout << "Final Color: " << finalColor << std::endl;
    // // exit(0);

    // return finalColor;
}

int counter = 0;

void RayTracer::drawSceneGlobalIllumination() {
    const double halfCircle = M_PI / 180;

    for(const auto& o : this->o) {
        const double fovOverTwoRadians = (o->fov / 2) * halfCircle;
        float delta = (2 * tan(fovOverTwoRadians)) / (float)(o->size[1]);
        Eigen::Vector3f upperLeftCorner = o->camera + o->lookat + (tan(fovOverTwoRadians) * o->up) + ((float)o->size[0]/2 * delta * o->left);
        std::vector<double> buffer(3*o->size[0] * o->size[1]); 


        // direction vector maybe needs normalization
        // before shooting into scene
        for(int j{0}; j<o->size[1] ; j++) {
            for(int i{0}; i<o->size[0]; i++) {
                int notContributed = 0;
                Eigen::Vector3f totalColor(0,0,0);
                for(int k{0}; k<o->raysperpixel[1]*2; k++){
                    Eigen::Vector3f pixelColor(0,0,0);
                    Ray ray(o->camera, upperLeftCorner - (i*delta + delta/2)*o->left - (j*delta - delta/2)*o->up - o->camera);
                    rayColorGlobalIllumination(ray, o, pixelColor, 0);
                    if(pixelColor == o->bkc) {
                        totalColor = o->bkc;
                        break;
                    }
                    else if(pixelColor == Eigen::Vector3f(-1,-1,-1)) {
                        notContributed++;
                    }
                    else {
                        totalColor += pixelColor;
                        // std::cout << "not contributed: " << notContributed << std::endl;
                        // std::cout << "total color: " << totalColor << std::endl;
                    }
                    
                }

                if(totalColor != Eigen::Vector3f(0,0,0)){
                    if(totalColor != o->bkc){
                        totalColor /= o->raysperpixel[1]*2-notContributed;
                    }
                }
                buffer[3*j*o->size[0]+3*i+1]=totalColor.y();
                buffer[3*j*o->size[0]+3*i+2]=totalColor.z();
                buffer[3*j*o->size[0]+3*i+0]=totalColor.x();
                // potential divide by 0 error
                // totalColor /= (1-notContributed);
                
            }
        }
        save_ppm(o->filename,buffer,o->size[0],o->size[1]);
    }
}

void RayTracer::run() {
    extractSceneFromJSON();
    drawScene();
}