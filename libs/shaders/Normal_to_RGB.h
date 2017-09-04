#ifndef NORMAL_TO_RGB_H_
#define NORMAL_TO_RGB_H_
#include "../Shader.h"

  class Normal_to_RGB : public Shader{
  public:

    Normal_to_RGB():Shader(){};
    RGB shade(const Ray &ray, const Scene &scene) const override;

  };

  RGB Normal_to_RGB::shade(const Ray &ray, const Scene &scene) const {
    float max_t = std::numeric_limits<float>::max();
    float min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      rgb_to_paint = 0.5 * (rec.normal + Vector3(1,1,1));

    }
    else{

      rgb_to_paint = interpolate_background(ray, scene.get_background());

    }

    return rgb_to_paint;
  }
#endif
