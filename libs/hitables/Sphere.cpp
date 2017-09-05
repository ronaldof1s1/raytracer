#include "Sphere.h"
bool Sphere::hit(const Ray & r, float t_min, float t_max, hit_record & rec) const {

    //bhaskara to see if the ray collides with the sphere

    Vector3 oc = r.get_origin() - center;

    float a = dot(r.get_direction(), r.get_direction());
    float b = 2 * dot(oc, r.get_direction());
    float c = dot(oc,oc) - radius*radius;

    float delta = b*b - 4*a*c;

    if (delta >= 0) { //means that the ray colides with the sphere
        float t1 = (-b - sqrt(delta))/(2.0*a);
        float t2 = (-b + sqrt(delta))/(2.0*a);

        //now we try to get the minimum positive of the t's
        //which is closests to the ray origin.
        //Or we return false

        if(t1 > t_min && t1 < t_max){
            if(t1 < t2 || t2 < 0){
            rec.t = t1;
            rec.p = r.point_at(t1);
            rec.normal = (rec.p - center)/radius; //already normalized
            rec.material = material;
            return true;
            }
        }
        if(t2 > t_min && t2 < t_max){
            rec.t = t2;
            rec.p = r.point_at(t2);
            rec.normal = (rec.p - center)/radius; //already normalized
            rec.material = material;
            return true;
        }
    }
    return false; //if not hit sphere, or sphere is behind ray origin
};
