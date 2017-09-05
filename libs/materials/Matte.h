#ifndef MATTE_H_
#define MATTE_H_
#include "../Material.h"

class Matte : public Material{
public:
  RGB albedo;
  Matte():Material(){
    albedo = RGB(0,0,0);
  }

  Matte(RGB rgb_):Material(rgb_){
    albedo = RGB(0,0,0);
  }

  Matte(RGB a, RGB rgb_):Material(rgb_){
    albedo = a;
  }

  Matte(RGB a, RGB rgb_, float k_a_, float k_d_, float k_s_): Material(rgb_, k_a_, k_d_, k_s_) {
    albedo = a;
  }
};

#endif
