#include "Sphere.h"
bool Sphere::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {

    //bhaskara to see if the ray collides with the sphere

    Point3 ray_origin = r.get_origin();
    Vector3 ray_direction = r.get_direction();

    ray_origin = transform_inverse.transform_point(ray_origin);
    ray_direction = transform_inverse.transform_vector(ray_direction);

    Vector3 oc = ray_origin - center;

    double a = dot(ray_direction, ray_direction);
    double b = 2 * dot(oc, ray_direction);
    double c = dot(oc,oc) - radius*radius;

    double delta = b*b - 4*a*c;

    if (delta >= 0) { //means that the ray colides with the sphere
        double t1 = (-b - sqrt(delta))/(2.0*a);
        double t2 = (-b + sqrt(delta))/(2.0*a);

        //now we try to get the minimum positive of the t's
        //which is closests to the ray origin.
        //Or we return false
        Ray new_ray(ray_origin, ray_direction);

        if(t1 > t_min && t1 < t_max){
            if(t1 < t2 || t2 < 0){
            rec.t = t1;
            rec.p = new_ray.point_at(t1);
            Vector3 normal = unit_vector((rec.p - center)/radius);
            // rec.normal = transform.transform_vector(normal);
            rec.normal = normal;
            rec.material = material;
            return true;
            }
        }
        if(t2 > t_min && t2 < t_max){
            rec.t = t2;
            rec.p = new_ray.point_at(t2);
            Vector3 normal = unit_vector((rec.p - center)/radius);
            // rec.normal = transform.transform_vector(normal);
            rec.normal = normal;
            rec.material = material;
            return true;
        }
    }
    return false; //if not hit sphere, or sphere is behind ray origin
};
