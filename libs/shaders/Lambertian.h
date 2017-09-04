#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Shader.h"
#include <random>

class Lambertian : public Shader{
  int iterations;
public:

  Lambertian():Shader(){ iterations = 1; };
  Lambertian(int iter):Shader(){ iterations = iter;}

  Vector3 random_unit_vector();
  RGB Shade(const Ray &ray, const Scene &scene) const override;
  RGB Shade(const Ray &ray, const Scene &scene, int iteration);

};

  Vector3 Lambertian::random_unit_vector(){
    Vector3 v;
    do {
      std::knuth_b random_generator(time(0));
      float x = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
      float y = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
      float z = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);

      v = 0.5 * Vector3(x,y,z) + Vector3(1,1,1)
    } while(dot(v,v) >= 1.0);

    return v;
  }

  RGB Lambertian::Shade(const Ray &ray, const Scene &scene) const {
    
  }
#endif
