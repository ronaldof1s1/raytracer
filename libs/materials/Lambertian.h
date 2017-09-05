#ifndef LAMBERTIAN_MATERIAL_H_
#define LAMBERTIAN_MATERIAL_H_

#include "../Material.h"

class Lambertian : public Material{
public:
  Lambertian():Material(){}
  Lambertian(RGB rgb_ ):Material(rgb_){}
  Lambertian(RGB k_a, RGB k_d, RGB k_s):Material(k_a, k_d, k_s){}
};

#endif
