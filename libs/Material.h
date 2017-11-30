#ifndef MATERIAL_H_
#define MATERIAL_H_
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
    RGB albedo; // The coefficient of diffuse reflectance


    //Constructors
    Material(){
      albedo = RGB(0.d); //Black sphere

    }
    Material(RGB rgb){
      albedo = rgb;
    }

    Vector3 reflect(const Vector3 &v_in, const Vector3 &normal) const {
      return v_in - 2*dot(v_in, normal)*normal;
    }

		//using snell law = n1 * sin1 = n2 * sin2
		bool refract(const Vector3 &v_in, const Vector3 &normal, double n, Vector3 &refracted) const{
			double cos_incident_normal = dot(unit_vector(v_in), normal);
			double sin_T2 = n*n *(1 - cos_incident_normal * cos_incident_normal);
			if(sin_T2 > 1){
				return false;
			}
			double cos_T = sqrt(1- sin_T2);
			refracted = n*(v_in- n*cos_incident_normal) - n*cos_T;
			return true;
		}

		double reflectance(const Vector3 &v_in, const Vector3 &normal, double n1, double n2) const {
			double n = n1/n2;
			double cos_incident_normal = dot(v_in, normal);
			double sin_T2 = n*n *(1 - cos_incident_normal * cos_incident_normal);
			if(sin_T2 > 1){
				return 1;
			}
			double cos_T = sqrt(1- sin_T2);
			double r_0rth = (n1 * cos_incident_normal - n2 * cos_T)/(n1 * cos_incident_normal + n2 * cos_T);
			double r_par = (n2 * cos_incident_normal - n1 * cos_T) / (n2 * cos_incident_normal + n1 * cos_T);
			return (r_0rth * r_0rth + r_par * r_par) / 2;
		}

    virtual bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const = 0;
  };
#endif
