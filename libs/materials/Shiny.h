#ifndef SHINY_H_
#define SHINY_H_

#include "../Material.h"
#include "../textures/Constant_Texture.h"

class Shiny : public Material{
public:
  RGB k_a, k_s;
  double specular_exponent;
  //Constructors
  Shiny(double exponent = 4):Material(RGB(0)){
    k_a = k_s = RGB(0);
    specular_exponent = exponent;
  }
  Shiny(Texture *texture, RGB k_a_, RGB k_s_, double exponent = 4):Material(texture){
    k_a = k_a_;
    k_s = k_s_;
    specular_exponent = exponent;
  }
  bool scatter(const Ray &ray_in,  const hit_record &rec, Ray &scattered) const override;
};
bool Shiny::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  Vector3 target = rec.p + rec.normal + random_vector_in_unit_sphere();
  Point3 origin = rec.p + 0.01 * rec.normal;
  scattered = Ray(origin, target - origin);
  return true;
}
#endif
