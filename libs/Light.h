#ifndef LIGHT_H_
#define LIGHT_H_

class Light {

  public:
    RGB intensity;
    
    //Constructors
    Light(){
      intensity = RGB(1.0,1.0,1.0);
    }
    Light(RGB rgb){
      intensity = rgb;
    }
    
    RGB get_intensity(){ return intensity; }

    virtual Vector3 get_direction() const = 0;
  };
#endif
