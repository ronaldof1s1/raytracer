#ifndef MATTE_H_
#define MATTE_H_
#include "../Material.h"

class Matte : public Material{
public:
  Matte(){
    albedo = RGB(0,0,0);
    rgb = RGB(1,1,1);
  }

  Matte(RGB rgb_){
    rgb = rgb_;
    albedo = RGB(0,0,0);
  }

  Matte(RGB a, RGB rgb_){
    rgb = rgb_;
    albedo = a;
  }
};

#endif
