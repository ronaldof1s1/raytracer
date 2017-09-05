#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "../Shader.h"
#include <cmath>
#include <random>
#include <algorithm>

class BlinnPhong : public Shader{
  int iterations;
public:

  BlinnPhong():Shader(){ iterations = 1; };
  BlinnPhong(int iter):Shader(){ iterations = iter;}

  Vector3 random_vector_in_unit_sphere() const;
  RGB shade(const Ray &ray, const Scene &scene) const override;
  RGB shade(const Ray &ray, const Scene &scene, int iteration) const;

};

Vector3 BlinnPhong::random_vector_in_unit_sphere() const{
    Vector3 v;
    do {
      std::knuth_b random_generator(time(0));
      float x = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
      float y = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
      float z = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);

      v = 2 * Vector3(x,y,z) - Vector3(1,1,1);
    } while(dot(v,v) >= 1.0);

    return v;
}

RGB BlinnPhong::shade(const Ray &ray, const Scene &scene) const {
    float max_t = std::numeric_limits<float>::max();
    float min_t = 0.0;

    RGB ambientLight = RGB(0.4,0.4,0.4);
    RGB rgb_to_paint = RGB(0,0,0);
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      /*if(iteration >= 1){
        Vector3 target = rec.normal + random_vector_in_unit_sphere();
        Vector3 unit_light = unit_vector(scene.get_light_source()-rec.p);
        /*float cos_ = dot(unit_light, rec.normal);
        if(cos_ <= 0){
          rgb_to_paint = RGB(0,0,0);
        }
        else{
          // std::cout << rec.material->rgb;
          rgb_to_paint = 0.5 * shade(Ray(rec.p, target), scene, --iteration);
        //}
      }
      else{
        rgb_to_paint = RGB(0,0,0);
      }*/

      rgb_to_paint += rec.material->k_a * ambientLight; // Add the ambient light


      auto lights = scene.get_lights();
      for (auto it = lights.begin(); it != lights.end(); it++)
      {
        Vector3 unit_light = unit_vector(scene.get_light_source()-rec.p);
        float cos_ = dot(unit_light, rec.normal);

        if(cos_ <= 0){
          rgb_to_paint += RGB(0,0,0);
        }
        else{
        	rgb_to_paint += (rec.material->k_d * it->intensity) * cos_;
        }

        Vector3 halfway_vector = unit_vector(unit_light - ray);
        float dot_n_h = dot(rec.normal, halfway_vector);
        int expoent = 16;
        dot_n_h = std::pow(dot_n_h, expoent * 4);

        rgb_to_paint += (rec.material->k_s * it->intensity) * dot_n_h;
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

  RGB BlinnPhong::shade(const Ray &ray, const Scene &scene) const {
    return shade(ray, scene, iterations);
  }
#endif