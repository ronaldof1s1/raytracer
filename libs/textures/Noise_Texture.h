#ifndef NOISE_TEXTURE_H_
#define NOISE_TEXTURE_H_

#include "../Texture.h"
#include "../utility/Perlin.h"

class Noise_Texture : public Texture{
public:
  RGB color;
  Perlin noise;
  double scale;

  Noise_Texture(RGB color, double scale = 1) : color(color), scale(scale){noise = Perlin();}

  virtual Vector3 value(double u, double v, Point3& p) override;
};

Vector3 Noise_Texture::value(double u, double v, Point3& p){
  return color*0.5*(1 + sin(scale*p.x() + 5*noise.turb(scale*p)));
}

#endif
