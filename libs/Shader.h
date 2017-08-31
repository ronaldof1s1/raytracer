#ifndef SHADER_H_
#define SHADER_H_
#include "utility/Ray.h"
#include "Scene.h"

  class Shader{
  public:
    virtual RGB shade(Ray &ray, Scene &scene) const = 0;
  };

#endif
