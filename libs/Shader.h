#ifndef SHADER_H_
#define SHADER_H_
#include "utility/Ray.h"
#include "Scene.h"

  class Shader{
  public:
    virtual RGB shade(const Ray &ray, const Scene &scene) const = 0;
    RGB interpolate_background(const Ray &ray, const Background &background) const;
  };

    RGB Shader::interpolate_background(const Ray &ray, const Background &background) const{
      RGB unit_direction = unit_vector(ray.get_direction());
      float x = 0.5*(unit_direction.x() + 1);

      RGB bottom = (1-x)*background.lower_left + x * background.lower_right;
      RGB top = (1-x)*background.upper_left + x * background.upper_right;

      float y = 0.5*(unit_direction.y() + 1);
      return (1-y) * top + y * bottom;
    }

#endif
