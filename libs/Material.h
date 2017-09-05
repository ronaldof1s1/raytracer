#ifndef MATERIAL_H_
#define MATERIAL_H_
  class Material {
  public:
    RGB k_a; // The coefficient of ambient light
    RGB k_d; // The coefficient of diffuse reflectance
    RGB k_s; // The coefficient of specular reflectance

    Material(){
      k_a = RGB(1,1,1);
      k_d = RGB(0,0,0);
      k_s = RGB(0,0,0);
    }
    Material(RGB rgb_){
      k_a = RGB(1,1,1);
      k_d = rgb_;
      k_s = RGB(0,0,0);
    }

    Material(RGB k_a_, RGB k_d_, RGB k_s_ ){
      k_a = k_a_;
      k_d = k_d_;
      k_s = k_s_;
    }
  };
#endif
