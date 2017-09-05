#ifndef LAMBERTIAN_MATERIAL_H_
#define LAMBERTIAN_MATERIAL_H_

#include "../Material.h"

class Lambertian_material : public Material{
public:
  Lambertian_material():Material(){}
  Lambertian_material(RGB rgb_ ):Material(rgb_){}
  Lambertian_material(RGB k_a, RGB k_d, RGB k_s):Material(k_a, k_d, k_s){}
};

#endif
