#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Material.h"

class Lambertian : public Material{
public:
  //Constructors
  Lambertian():Material(){}
  Lambertian(RGB rgb_ ):Material(rgb_){}
  Lambertian(RGB k_a, RGB k_d):Material(k_a, k_d, RGB(0.0)){}
};

#endif
