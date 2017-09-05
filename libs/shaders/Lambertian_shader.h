#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Shader.h"
#include <random>

class Lambertian : public Shader{
  int iterations;
public:

  Lambertian():Shader(){ iterations = 1; };
  Lambertian(int iter):Shader(){ iterations = iter;}

  Vector3 random_vector_in_unit_sphere() const;
  RGB shade(const Ray &ray, const Scene &scene) const override;
  RGB shade(const Ray &ray, const Scene &scene, int iteration) const;

};

  Vector3 Lambertian::random_vector_in_unit_sphere() const{
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

  RGB Lambertian::shade(const Ray &ray, const Scene &scene, int iteration) const {
    float max_t = std::numeric_limits<float>::max();
    float min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      if(iteration >= 1){
        for(auto light = scene.lights.begin(); light != scene.lights.end(); light++){
          Vector3 target = rec.normal + random_vector_in_unit_sphere();
          // Vector3 unit_light = unit_vector(scene.get_light_source() - rec.p);
          Vector3 unit_light = unit_vector(light->source - rec.p);
          float cos_ = dot(unit_light, rec.normal);
          if(cos_ <= 0){
            rgb_to_paint = RGB(0,0,0);
          }
          else{
            // std::cout << rec.material->rgb;
            // rgb_to_paint = rec.material->k_d * rec.material->rgb * shade(Ray(rec.p + Vector3(0.01,0.01,0.01), target), scene, --iteration);
            // std::cout << "RGB: " << rec.material->k_d * rec.material->rgb;
            rgb_to_paint += light->intensity * rec.material->k_d * shade(Ray(rec.p + Vector3(0.01,0.01,0.01), target), scene, --iteration);
          }
        }
      }
      else{
        rgb_to_paint = RGB(0,0,0);
      }
    }
    else{

      rgb_to_paint = interpolate_background(ray, scene.get_background());

    }

    return rgb_to_paint;
  }

  RGB Lambertian::shade(const Ray &ray, const Scene &scene) const {
    return shade(ray, scene, iterations);
  }
#endif
