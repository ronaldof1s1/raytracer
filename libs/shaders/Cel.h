#ifndef CEL_H_
#define CEL_H_
#include "../Shader.h"
#include <vector>
#include <cmath>
#include <algorithm>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class Cel : public Shader{
  std::vector<int> shading_intervals;
  double outline_threshold;
public:
  Cel(double threshold = 80):Shader(){shading_intervals.push_back(45); outline_threshold = threshold;};
  Cel(std::vector<int> intervals, double threshold = 80):Shader(){
    std::sort(intervals.begin(), intervals.end());
    shading_intervals = intervals;
    outline_threshold = threshold;
   }

  virtual RGB shade(const Ray &ray, const Scene &scene) const override; //Override method from Shader.h

};

RGB Cel::shade(const Ray &ray, const Scene &scene) const{
  double max_t = std::numeric_limits<double>::max();
  double min_t = 0.0;

  RGB rgb_to_paint = RGB(0);
  hit_record rec;


  if(scene.hit_anything(ray, min_t, max_t, rec)){
    double cos_cam_normal = dot(-ray.get_direction(), rec.normal);

    if(cos_cam_normal > std::cos(80 * M_PI/180)){

      auto lights = scene.get_lights();
      Point3 origin = rec.p + rec.normal * 0.01;

      for(auto light : lights){
        Vector3 light_direction = unit_vector(light.source - origin);
        if(is_shadow(Ray(origin, light_direction), scene)){
          // rgb_to_paint = rec.material->shadow;
          rgb_to_paint = RGB(0,1,0);
          continue;
        }
        double cos_light_normal = dot(light_direction, rec.normal);
        RGB light_rgb;
        for(double interval : shading_intervals){

          double cos_interval = std::cos(interval * M_PI/180);

          if(cos_light_normal > cos_interval){

            light_rgb = RGB(1,0,0) * cos_interval;
            break;

          }
        }
        rgb_to_paint += light_rgb;
      }
    }
    else{
      //rgb_to_paint = rec.material->outline
      rgb_to_paint = RGB(0,0,1);
    }
  }
  else{
    rgb_to_paint = interpolate_background(ray, scene.get_background());
  }
  return rgb_to_paint;
};

#endif
