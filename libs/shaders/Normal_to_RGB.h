#ifndef NORMAL_TO_RGB_H_
#define NORMAL_TO_RGB_H_
#include "../Shader.h"

  class Normal_to_RGB : public Shader{
  public:
    Normal_to_RGB(){}

    virtual RGB shade(Ray &ray, Scene &scene);

  };

  RGB shade(Ray &ray, Scene &scene){
    	    float max_t = std::numeric_limits<float>::max();
    	    float min_t = 0.0;

    	    Vector3 rgb_to_paint;
    	    hit_record rec;

    	    if(Scene_.hit_anything(r_, min_t, max_t, rec)){

	          rgb_to_paint = 0.5 * (rec.normal + Vector3(1,1,1));

    	      return rgb_to_paint;
    	    }

          RGB unit_direction = unit_vector(r_.get_direction());
          float x = 0.5*(unit_direction.x() + 1);

    	    RGB bottom = (1-x)*scene.get_background().lower_left + x * scene.get_background().lower_right;
    	    RGB top = (1-x)*scene.get_background().upper_left + x * scene.get_background().upper_right;

          float y = 0.5*(unit_direction.y() + 1);
    	    rgb_to_paint = (1-y) * top + y * bottom;

    	    return rgb_to_paint; // Stub, replace it accordingly
  }
#endif
