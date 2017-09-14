#ifndef SHINY_H_
#define SHINY_H_

#include "../Material.h"

class Shiny : public Material{
public:
  //Constructors
  Shiny():Material(){}
  Shiny(RGB k_a, RGB k_d, RGB k_s, double specular_exponent = 4):Material(k_a, k_d, k_s, specular_exponent){}
  bool scatter(const Ray &ray_in,  hit_record &rec, Ray &scattered) const override;
};
bool Shiny::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {

}
#endif
