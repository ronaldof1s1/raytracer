#ifndef MATERIAL_H_
#define MATERIAL_H_
  class Material {
  public:
    RGB rgb;
    
    Material(){
      rgb = RGB(1,1,1);
    }
    Material(RGB rgb_){
      rgb = rgb_;
    }
  };
#endif
