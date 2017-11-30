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
		bool refract(const Vector3 &v, const Vector3 &n, double ni_over_nt, Vector3 &refracted) const{

			Vector3 uv = unit_vector(v);
			double dt = dot(uv, n);
			double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1-dt*dt);

			if(discriminant > 0){
				refracted = ni_over_nt *(v - n*dt) - n*sqrt(discriminant);
				// std::cout << "vect " << (unit_vector(v) - unit_vector(refracted)).length() << '\n';
				// std::cout << "ni_over_nt" << ni_over_nt << '\n';
				// std::cout << "v" << v << '\n';
				// std::cout << "n" << n << '\n';
				// refracted = Vector3(0,1,0);

				return true;
			}
			else
				return false;
		}
		// bool refract(const Vector3 &v_in, const Vector3 &normal, double n, Vector3 &refracted) const{
		// 	Vector3 uv = unit_vector(v_in);
		// 	double cos_incident_normal = dot(uv, unit_vector(normal));
		// 	double sine = 1 - cos_incident_normal * cos_incident_normal;
		// 	double discriminant = 1 - n*n *(sine);
		// 	if(discriminant <= 0){
		// 		return false;
		// 	}
		// 	double cos_T = sqrt(discriminant);
		// 	refracted = n*(uv- normal*cos_incident_normal) - normal*cos_T;
		// 	return true;
		// }



    virtual bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const = 0;
  };
#endif
