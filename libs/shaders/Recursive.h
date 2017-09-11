#ifndef RECURSIVE_H_
#define RECURSIVE_H_  

#include "../Shader.h"
#include <random>
#include <algorithm>

class Recursive : public Shader{

  int iterations; //Number of iterations

public:


  //===>Constructors
  Recursive():Shader(){ iterations = 1; };
  Recursive(int iter):Shader(){ iterations = iter;}
  Recursive(int iter, bool amb, bool diff, bool spec = false):Shader(amb, diff, spec){ iterations = iter;}

  //setter

  //===>Methods

  //Create a random vector inside a sphere of radius 1
  Vector3 random_vector_in_unit_sphere() const;

  //Calls the other shade with iterations
  RGB shade(const Ray &ray, const Scene &scene) const override;

  //Actually gets the color
  RGB shade(const Ray &ray, const Scene &scene, int iteration) const;

};

//Global random generator with seed = 1
std::knuth_b random_generator(1);

  //Create a random vector inside a sphere of radius = 1
  //used for random direction of reflected ray
  Vector3 Recursive::random_vector_in_unit_sphere() const{

    Vector3 v;
    do {
      //Get random x, y and z
      double x = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
      double y = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
      double z = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);

      v = 2 * Vector3(x,y,z) - Vector3(1);//normalize between [0,1]
    } while(dot(v,v) >= 1.0); //until len^2 < 1

    return v;
  }

  //real color function, with number of iterations
  RGB Recursive::shade(const Ray &ray, const Scene &scene, int iteration) const {
    double max_t = std::numeric_limits<double>::max();
    double min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      if(iteration > 0){ //para chamadas recursivas

        //creates a unit vector for the direction of the reflected ray
        Vector3 target = unit_vector( rec.normal + random_vector_in_unit_sphere() );

        //for the first iteration we do kind of an antialiasing for the color
        if(iteration == iterations){

          for(int i = 0; i > 10; i++){
            //creates a unit vector for the direction of the reflected ray
            target = unit_vector( rec.normal + random_vector_in_unit_sphere() );

            // creates new ray with origin on point that was hit (with a slight add of 0.1 for evading
            // collision inside the sphere), and the direction is the target vector;
            Vector3 origin = rec.p + (rec.normal * Vector3(0.01));
            Ray new_ray(origin, target);

            // sums the painting rgb with the diffuse coefficient of the material * the recursive Call
            // use_diffuse is 1 if this shader use the diffuse coefficient;
            rgb_to_paint += rec.material->k_d * shade(new_ray, scene, iteration - 1) * use_diffuse;
          }
          //get mean of the colors from this "antialiasing"
          rgb_to_paint /= 10;
        }

        // now, for each pontual light, we have to get the light action on the object
        for(auto light = scene.lights.begin(); light != scene.lights.end(); light++){

          // Here we create a vector in the direction of the light, from the point hit
          Vector3 unit_light = unit_vector(light->source - rec.p);

          //calculate the cossene with the normal of that point
          double cos_light_normal = dot(unit_light, rec.normal);
          cos_light_normal = std::max(0.0, cos_light_normal); //cos < 0 means the light did not hit surface

            // then we sum the color with the light intensity applyed to the
            // diffuse coefficient, applyed to the conssene we found
          rgb_to_paint += cos_light_normal * light->intensity * rec.material->k_d * use_diffuse;



        }

        // creates new ray with origin on point that was hit (with a slight add of 0.1 for evading
        // collision inside the sphere), and the direction is the target vector;
        Vector3 origin = rec.p + (rec.normal * Vector3(0.01,0.01,0.01));
        Ray new_ray(origin, target);

        //gets the ambient light applied to the ambient coefficient of the material
        rgb_to_paint += rec.material->k_a * scene.get_ambient_light() * use_ambient;

        // sums with the recursive call applied to the diffuse coeficient
        rgb_to_paint +=  rec.material->k_d * shade(new_ray, scene, iteration) * use_diffuse;

      }
      else{ // the number of iterations hits it's maximum
        rgb_to_paint = RGB(0,0,0); // return black
      }
    }
    else{
      // if the ray hits the background, returns the background color,
      // interpolated at the point that was hit
      rgb_to_paint = interpolate_background(ray, scene.get_background());

    }

    // now we truncate the color to paint to 1, if greater;
    rgb_to_paint.e[0] = std::min(1.d, rgb_to_paint.r());
    rgb_to_paint.e[1] = std::min(1.d, rgb_to_paint.g());
    rgb_to_paint.e[2] = std::min(1.d, rgb_to_paint.b());


    return rgb_to_paint;
  }

  //calls the real shade function with iterations parameter
  RGB Recursive::shade(const Ray &ray, const Scene &scene) const {
    return shade(ray, scene, iterations);
  }
#endif
