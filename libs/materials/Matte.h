#ifndef MATTE_H_
#define MATTE_H_
#include "../Material.h"

class Matte : public Material{
public:
  Matte():Material(){
  }

  Matte(RGB rgb_):Material(rgb_){
  }


  Matte(RGB k_a_, RGB k_d_, RGB k_s_): Material( k_a_, k_d_, k_s_) {
  }
};

#endif
