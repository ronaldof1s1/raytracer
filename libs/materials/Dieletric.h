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

double schlick(double cosine, double ref_index){
  double r0 = (1 - ref_index) / ( 1 + ref_index );
  r0 *= r0;
  return r0 + ( 1 - r0 ) * pow( (1 - cosine) , 5 );
};


bool Dieletric::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {

  Vector3 ray_dir = unit_vector(ray_in.get_direction());
  Vector3 u_normal = unit_vector(rec.normal);
  double cos_dir_normal = dot(ray_dir, u_normal);
  Vector3 outward_normal;
  Vector3 reflected = reflect(ray_in.get_direction(), rec.normal);

  double n1_over_n2;
  // RGB atenuation = RGB(1);

  Vector3 refracted;

  double reflect_prob;
  double cosine;

  if(cos_dir_normal > 0) {
    outward_normal = -rec.normal;
    n1_over_n2 = refraction_index;
    cosine = refraction_index * cos_dir_normal;
  }
  else{
    outward_normal = rec.normal;
    n1_over_n2 = 1/refraction_index;
    cosine = - cos_dir_normal;
  }
  Vector3 origin = rec.p - 0.001*outward_normal;

  if(refract(ray_in.get_direction(), outward_normal, n1_over_n2, refracted)){
    reflect_prob = schlick(cosine, refraction_index);
  }
  else{
    scattered = Ray(origin, reflected);
    reflect_prob = 1;
  }
  // random_generator = std::knuth_b(3);
  double random_number = std::generate_canonical<double, std::numeric_limits<double>::digits>(random_generator) ;
  // std::cout << "reflect_prob" << reflect_prob << '\n';
  // std::cout << "random_number" << random_number << '\n';
  if(random_number > reflect_prob){
    scattered = Ray(origin, refracted);
  }
  else{
    scattered = Ray(origin, reflected);
  }

  return true;
}


#endif
