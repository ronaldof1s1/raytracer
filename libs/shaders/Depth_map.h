#ifndef DEPTH_MAP_H_
#define DEPTH_MAP_H_
#include "../Shader.h"

  class Depth_map : public Shader{
    float max_depth;
  public:
    Depth_map():Shader(){
      max_depth = 4.0;
    }
    Depth_map(float depth):Shader(){
      max_depth = depth;
    }

    float get_max_depth(){return max_depth;}
    virtual RGB shade(const Ray &ray, const Scene &scene) const override;

  };

  RGB Depth_map::shade(const Ray &ray, const Scene &scene) const{

    float max_t = std::numeric_limits<float>::max();
    float min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    RGB background_color(1,1,1);
	  RGB foreground_color(0,0,0);

    if(scene.hit_anything(ray, min_t, max_t, rec)){


  	  float depth = (rec.p - ray.get_origin()).length();
  	  depth /= max_depth;

  	  // evading color overflow
  	  if(depth > 1){
  	    depth = 1.0;
  	  }

  	  rgb_to_paint = (1.0 - depth) * (foreground_color) + depth * background_color;

      return rgb_to_paint;
    }


    return background_color;

  }
#endif
