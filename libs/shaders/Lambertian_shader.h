#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Shader.h"
#include <random>
#include <algorithm>

class Lambertian : public Shader{
  int iterations;
public:

  Lambertian():Shader(){ iterations = 1; };
  Lambertian(int iter):Shader(){ iterations = iter;}

  Vector3 random_vector_in_unit_sphere() const;
  RGB shade(const Ray &ray, const Scene &scene) const override;
  RGB shade(const Ray &ray, const Scene &scene, int iteration) const;

};

std::knuth_b random_generator(1);

  Vector3 Lambertian::random_vector_in_unit_sphere() const{
    Vector3 v;
    do {
      float x = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
      float y = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
      float z = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);

      v = 2 * Vector3(x,y,z) - Vector3(1,1,1);
    } while(dot(v,v) >= 1.0);

    return v;
  }

  RGB Lambertian::shade(const Ray &ray, const Scene &scene, int iteration) const {
    float max_t = std::numeric_limits<float>::max();
    float min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      if(iteration >= 1){

        Vector3 target = unit_vector( rec.normal + random_vector_in_unit_sphere() );


        if(iteration == iterations){
          for(int i = 0; i > 10; i++){
            target = unit_vector( rec.normal + random_vector_in_unit_sphere() );

            Ray new_ray(rec.p + (rec.normal * Vector3(0.01,0.01,0.01)), target);
            rgb_to_paint += rec.material->k_d * shade(new_ray, scene, iteration - 1);
          }
          rgb_to_paint /= 10;
        }

        for(auto light = scene.lights.begin(); light != scene.lights.end(); light++){
          Vector3 unit_light = unit_vector(light->source - rec.p);
          float cos_ = dot(unit_light, rec.normal);
          if(cos_ <= 0){
            rgb_to_paint += RGB(0,0,0);
          }
          else{
            rgb_to_paint += cos_ * light->intensity * rec.material->k_d;
          }
        }
        Ray new_ray(rec.p + (rec.normal * Vector3(0.01,0.01,0.01)), target);

        iteration--;

        rgb_to_paint +=  rec.material->k_d * shade(new_ray, scene, iteration);

      }
      else{
        rgb_to_paint = RGB(0,0,0);
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

  RGB Lambertian::shade(const Ray &ray, const Scene &scene) const {
    return shade(ray, scene, iterations);
  }
#endif
