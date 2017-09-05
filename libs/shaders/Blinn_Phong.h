#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "../Shader.h"
#include <cmath>
#include <random>
#include <algorithm>

class Blinn_Phong : public Shader{
  int iterations;
public:

  Blinn_Phong():Shader(){ iterations = 1; };
  Blinn_Phong(int iter):Shader(){ iterations = iter;}
  Blinn_Phong(int iter, bool amb, bool diff, bool spec):Shader(amb, diff, spec){ iterations = iter;}
  Blinn_Phong(bool amb, bool diff, bool spec):Shader(amb, diff, spec){ iterations = 1; }

  Vector3 random_vector_in_unit_sphere() const;
  RGB shade(const Ray &ray, const Scene &scene) const override;
  //RGB shade(const Ray &ray, const Scene &scene, int iteration) const;

};

RGB Blinn_Phong::shade(const Ray &ray, const Scene &scene) const {
    float max_t = std::numeric_limits<float>::max();
    float min_t = 0.0;

    RGB rgb_to_paint = RGB(0);
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      rgb_to_paint += rec.material->k_a * scene.ambient_light * use_ambient; // Add the ambient light


      auto lights = scene.get_lights();
      for (auto light = lights.begin(); light != lights.end(); light++)
      {
        Vector3 unit_light = unit_vector(light->source);
        float cos_ = dot(unit_light, rec.normal);

        /*if(cos_ <= 0){
          rgb_to_paint += RGB(0,0,0);
        }
        else*/if(cos_ > 0){
        	rgb_to_paint += (rec.material->k_d * light->intensity) * cos_ * use_diffuse;
        }

        Vector3 halfway_vector = unit_vector(unit_light - ray.get_direction());
        float dot_n_h = dot(rec.normal, halfway_vector);
        dot_n_h = std::pow(dot_n_h, rec.material->shininess);

        rgb_to_paint += (rec.material->k_s * light->intensity) * dot_n_h * use_specular;
      }

    }
    else{

      rgb_to_paint = interpolate_background(ray, scene.get_background());

    }

    rgb_to_paint.e[0] = std::min(1.f, rgb_to_paint.r());
    rgb_to_paint.e[1] = std::min(1.f, rgb_to_paint.g());
    rgb_to_paint.e[2] = std::min(1.f, rgb_to_paint.b());

    return rgb_to_paint;
  }
#endif