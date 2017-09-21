#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "../Shader.h"
#include "../materials/Shiny.h"
#include <cmath>
#include <random>
#include <algorithm>

class Blinn_Phong : public Shader{
public:
  double use_ambient, use_diffuse, use_specular; //double to multiply if coefficients are used or no in the shader
  bool shadows; //activate shadows

  Blinn_Phong():Shader(){};
  Blinn_Phong(bool amb, bool diff, bool spec, bool shadow = true):Shader(){
    use_ambient = amb ? 1.0 : 0.0;
    use_ambient = diff ? 1.0 : 0.0;
    use_ambient = spec ? 1.0 : 0.0;
    shadows = shadow;
  };

  RGB shade(const Ray &ray, const Scene &scene) const override;

};

RGB Blinn_Phong::shade(const Ray &ray, const Scene &scene) const {
  double max_t = std::numeric_limits<double>::max();
  double min_t = 0.0;

  RGB rgb_to_paint = RGB(0);
  hit_record rec;

  if(scene.hit_anything(ray, min_t, max_t, rec)){
    Shiny *shiny = dynamic_cast<Shiny*>(rec.material);
    Lambertian *lambertian = dynamic_cast<Lambertian*>(rec.material);

    if (shiny == nullptr and lambertian == nullptr) {
      std::cerr << "material must be shiny or lambertian" << '\n';
      return RGB(0);
    }

    if(shiny != nullptr){
      rgb_to_paint += shiny->k_a * scene.ambient_light * use_ambient; // Add the ambient light
    }
    if(lambertian != nullptr){
      rgb_to_paint += lambertian->k_a * scene.ambient_light * use_ambient; // Add the ambient light
    }


    auto lights = scene.get_lights();
    for (auto light = lights.begin(); light != lights.end(); light++)
    {

      Point3 new_origin = rec.p + (rec.normal * Vector3(0.01));
      Vector3 light_direction = unit_vector(light->source - new_origin);
      Ray new_ray(new_origin, light_direction);
      if(!shadows or !is_shadow(new_ray, scene)){

        double cos_light_normal = dot(light_direction, rec.normal);
        cos_light_normal = std::max(0.0, cos_light_normal);

        RGB diffuse_intensity = light->intensity * cos_light_normal;

        rgb_to_paint += rec.material->albedo * diffuse_intensity * use_diffuse;

        // Vector3 vdir = unit_vector(ray.get_origin() - rec.p); // = -ray.get_direction
        if(shiny != nullptr){
          Vector3 halfway_vector = unit_vector(light_direction - ray.get_direction());
          double cos_normal_halfway = dot(rec.normal, halfway_vector);
          cos_normal_halfway = std::max(0.0, cos_normal_halfway);

          RGB shininess_intensity = light->intensity * std::pow(cos_normal_halfway, shiny->specular_exponent);

          rgb_to_paint += shiny->k_s * shininess_intensity * use_specular;
        }
      }
    }
  }
  else{
    rgb_to_paint = interpolate_background(ray, scene.get_background());
  }

    rgb_to_paint.e[0] = std::min(1.d, rgb_to_paint.r());
    rgb_to_paint.e[1] = std::min(1.d, rgb_to_paint.g());
    rgb_to_paint.e[2] = std::min(1.d, rgb_to_paint.b());

    return rgb_to_paint;
  }
#endif
