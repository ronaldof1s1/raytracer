#ifndef MATERIAL_H_
#define MATERIAL_H_
  class Material {
  public:
    RGB k_a; // The coefficient of ambient light
    RGB k_d; // The coefficient of diffuse reflectance
    RGB k_s; // The coefficient of specular reflectance

    int shininess; // Shininess coefficient for reflecting light on some shaders

    //Constructors
    Material(int sh=0){
      k_a = RGB(0.1f);
      k_d = RGB(0.d); //Black sphere
      k_s = RGB(0.d);
      shininess = sh;
    }
    Material(RGB rgb_, int sh=0){
      k_a = RGB(0.1f);
      k_d = rgb_;
      k_s = RGB(0.d);
      shininess = sh;
    }

    Material(RGB k_a_, RGB k_d_, RGB k_s_, int sh=0 ){
      k_a = k_a_;
      k_d = k_d_;
      k_s = k_s_;
      shininess = sh;
    }
  };
#endif
