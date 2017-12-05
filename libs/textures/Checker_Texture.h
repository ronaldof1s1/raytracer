#ifndef Checker_TEXTURE_H_
#define Checker_TEXTURE_H_

#include "Constant_Texture.h"

class Checker_Texture : public Texture{
public:
  Texture *odd, *even;

  Checker_Texture(RGB c1, RGB c2) {
    odd = new Constant_Texture(c1);
    even = new Constant_Texture(c2);
  };

  Checker_Texture(Texture *t1, Texture *t2) : odd(t1), even(t2) {}

  virtual Vector3 value(double u, double v, Point3& p) override;
};

Vector3 Checker_Texture::value(double u, double v, Point3& p){

  double sines = sin(10*p.x()) * sin(10 * p.y()) * sin(10*p.z());

  if(sines < 0){
    return odd->value(u, v, p);
  }
  else{
    return even->value(u, v, p);
  }

}

#endif
