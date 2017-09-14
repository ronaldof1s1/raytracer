#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Material.h"

class Lambertian : public Material{
public:
  //Constructors
  Lambertian():Material(){}
  Lambertian(RGB rgb_ ):Material(rgb_){}
  Lambertian(RGB k_a, RGB k_d):Material(k_a, k_d, RGB(0.0)){}
  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Lambertian::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  Vector3 target = rec.p + rec.normal + random_vector_in_unit_sphere();
  Point3 origin = rec.p + 0.01 * rec.normal;
  scattered = Ray(origin, target - origin);
  return true;
}

#endif
