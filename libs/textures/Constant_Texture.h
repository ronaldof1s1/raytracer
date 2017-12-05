#ifndef CONSTANT_TEXTURE_H_
#define CONSTANT_TEXTURE_H_

#include "Texture.h"

class Constant_Texture : public Texture{
public:
  Vector3 color;

  Constant_Texture(){}

  Constant_Texture(Vector3 c) : color(c) {};


  virtual Vector3 value(double u, double v, Point3& p) override;
};

Vector3 Constant_Texture::value(double u, double v, Point3& p){
  return color;
}

#endif
