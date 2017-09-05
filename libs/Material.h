#ifndef MATERIAL_H_
#define MATERIAL_H_
  class Material {
  public:
    RGB rgb;
    float k_a; // The coefficient of ambient light
    float k_d; // The coefficient of diffuse reflectance
    float k_s; // The coefficient of specular reflectance
    
    Material(){
      rgb = RGB(1,1,1);
      k_a = 1.0;
      k_d = 0;
      k_s = 0;
    }
    Material(RGB rgb_){
      rgb = rgb_;
      k_a = 1.0;
      k_d = 0;
      k_s = 0;
    }

    Material(RGB rgb_, float k_a_, float k_d_, float k_s_ ){
      rgb = rgb_;
      k_a = k_a_;
      k_d = k_d_;
      k_s = k_s_;
    }
  };
#endif
