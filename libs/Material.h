#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "textures/Constant_Texture.h"

class Material;
//struct to the point that was hit
struct hit_record {
	double t; //the t at the point
  Point3  p; //the point that was hit
  Vector3 normal; //the normal of the point in relation to the object
	Material *material; //the material that was hit
};
  class Material {

  public:
    Texture *texture; // the texture of the material


    //Constructors
    Material(){
      texture = new Constant_Texture(RGB(0.d)); //Black sphere

    }
    Material(RGB rgb){
      texture = new Constant_Texture(rgb);
    }
		Material(Texture *t) : texture(t) {}

    Vector3 reflect(const Vector3 &v_in, const Vector3 &normal) const {
      return v_in - 2*dot(v_in, normal)*normal;
    }

		//using snell law = n1 * sin1 = n2 * sin2
		bool refract(const Vector3 &v, const Vector3 &n, double ni_over_nt, Vector3 &refracted) const{

			Vector3 uv = unit_vector(v);
			double dt = dot(uv, n);
			double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1-dt*dt);

			if(discriminant > 0){
				refracted = ni_over_nt *(v - n*dt) - n*sqrt(discriminant);

				return true;
			}
			else
				return false;
		}

    virtual bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const = 0;
  };
#endif
