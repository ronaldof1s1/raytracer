#ifndef SHADER_H_
#define SHADER_H_
#include "utility/Ray.h"
#include "Scene.h"

  class Shader{
  protected:

    float use_ambient, use_diffuse, use_specular; //float to multiply if coefficients are used or no in the shader

  public:

    //Constructors
    Shader(){
      use_ambient = use_diffuse = use_specular = 1.f; //use all coefficients in the shaders
    }

    Shader(bool amb, bool diff, bool spec){
      use_ambient  = amb  ? 1.f : 0.f;
      use_diffuse  = diff ? 1.f : 0.f;
      use_specular = spec ? 1.f : 0.f;
    }


    //Methods

    //virtual, implement in other shaders
    virtual RGB shade(const Ray &ray, const Scene &scene) const = 0; //Main function to get color of a point, given a ray and the scene

    RGB interpolate_background(const Ray &ray, const Background &background) const; //Method to interpolate and generate the background
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
