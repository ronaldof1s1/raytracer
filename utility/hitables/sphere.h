#ifndef SPHERE_H_
#define SPHERE_H_

#include "../hitable.h"

class sphere : public hitable{


public:
    float radius;
    sphere(){
        center = point3(0,0,0);
        radius = 0.f;
    };
    sphere(point3 cen, float r){
        center = cen;
        radius = r;
    }

    float get_radius(){return radius;}

    virtual bool hit( const Ray & r, float t_min, float t_max, hit_record & rec) const;
};

bool sphere::hit(const Ray & r, float t_min, float t_max, hit_record & rec) const {
    vector3 oc = r.get_origin() - center;
    float a = dot(r.get_direction(), r.get_direction());
    float b = 2 * dot(oc, r.get_direction());
    float c = dot(oc,oc) - radius*radius;

    float delta = b*b - 4*a*c;
    
    if (delta >= 0) {
        float t1 = (-b + sqrt(delta))/(2.0*a);
        float t2 = (-b - sqrt(delta))/(2.0*a);
            
        if(t1 > t_min && t1 < t_max){
            if(t1 < t2 || t2 < 0){
            rec.t = t1;
            rec.p = r.point_at(t1);
            rec.normal = (rec.p - center)/radius;
            return true;
            }
        }
        if(t2 > t_min && t2 < t_max){
            rec.t = t2;
            rec.p = r.point_at(t2);
            rec.normal = (rec.p - center)/radius;
            return true;
        }
    }
    return false;
};

#endif
