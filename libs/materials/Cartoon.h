#ifndef CARTOON_H_
#define CARTOON_H_

#include "../Material.h"

class Cartoon : public Material{
  RGB shadow;
  RGB outline;
public:

  Cartoon():Material(){shadow = RGB(0); outline = RGB(0);};

  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Cartoon::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  scattered = rec.normal;
  return true;
}
#endif
