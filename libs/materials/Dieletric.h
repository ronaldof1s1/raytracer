#ifndef DIELETRIC_H_
#define DIELETRIC_H_

#include "../Material.h"
#include <random>

class Dieletric : public Material{
  double refraction_index;
public:
  Dieletric(double refraction_index_, RGB color = RGB(1)):Material(color){
    refraction_index = refraction_index_;
  }

  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

float schlick(float cosine, float ref_index){
  float r0 = (1-ref_index) / (1+ref_index);
  r0 *= r0;
  return r0 + (1-r0)*pow((1-cosine),5);
};


bool Dieletric::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {

  Vector3 ray_dir = ray_in.get_direction();

  Vector3 outward_normal;


  double n1_over_n2;
  // RGB atenuation = RGB(1);

  Vector3 refracted;

  double reflect_prob;
  double cosine;

  if(dot(ray_dir, rec.normal) > 0) {
    outward_normal = -rec.normal;
    n1_over_n2 = refraction_index;
    cosine = refraction_index * dot(ray_dir, rec.normal) / ray_dir.length();
  }
  else{
    outward_normal = rec.normal;
    n1_over_n2 = 1/refraction_index;
    cosine = -dot(ray_dir, rec.normal) / ray_dir.length();
  }

  if(refract(ray_dir, outward_normal, n1_over_n2, refracted)){
    reflect_prob = schlick(cosine, refraction_index);
  }
  else{
    reflect_prob = 1;
  }

  if(std::generate_canonical<double, std::numeric_limits<double>::digits>(random_generator) > reflect_prob){
    scattered = Ray(rec.p, refracted);
  }
  else{
    Vector3 reflected = reflect(ray_dir, rec.normal);
    scattered = Ray(rec.p, reflected);
  }

  return true;
}


#endif
