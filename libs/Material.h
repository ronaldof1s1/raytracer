#ifndef MATERIAL_H_
#define MATERIAL_H_
  class Material {
  public:
    RGB k_a; // The coefficient of ambient light
    RGB k_d; // The coefficient of diffuse reflectance
    RGB k_s; // The coefficient of specular reflectance

    int shininess; // add comment

    Material(int sh=4){
      k_a = RGB(0.1f);
      k_d = RGB(0.f);
      k_s = RGB(0.f);
      shininess = sh;
    }
    Material(RGB rgb_, int sh=4){
      k_a = RGB(0.1f);
      k_d = rgb_;
      k_s = RGB(0.f);
      shininess = sh;
    }

    Material(RGB k_a_, RGB k_d_, RGB k_s_, int sh=4 ){
      k_a = k_a_;
      k_d = k_d_;
      k_s = k_s_;
      shininess = sh;
    }
  };
#endif
