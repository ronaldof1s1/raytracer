#include "Sphere.h"
bool Sphere::hit(const Ray & r, float t_min, float t_max, hit_record & rec) const {
    Vector3 oc = r.get_origin() - center;
    float a = dot(r.get_direction(), r.get_direction());
    float b = 2 * dot(oc, r.get_direction());
    float c = dot(oc,oc) - radius*radius;

    float delta = b*b - 4*a*c;

    if (delta >= 0) {
        float t1 = (-b - sqrt(delta))/(2.0*a);
        float t2 = (-b + sqrt(delta))/(2.0*a);

        if(t1 > t_min && t1 < t_max){
            if(t1 < t2 || t2 < 0){
            rec.t = t1;
            rec.p = r.point_at(t1);
            rec.normal = (rec.p - center)/radius;
            rec.material = material;
            return true;
            }
        }
        if(t2 > t_min && t2 < t_max){
            rec.t = t2;
            rec.p = r.point_at(t2);
            rec.normal = (rec.p - center)/radius;
            rec.material = material;
            return true;
        }
    }
    return false;
};
