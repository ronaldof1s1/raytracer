#include "Cube.h"

void Cube::set_transformation_matrix(Matrix t) {
  for(auto triangle : triangles){
		triangle->set_transformation_matrix(t);
  }
  transform = t;
}


bool Cube::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {
  // std::cout << "triangles size" << triangles.size() << '\n';
  bool hit_any_triangle = false;
  for(auto triangle : triangles){
    if(triangle->hit(r, t_min, t_max, rec)){
      t_max = rec.t;
      hit_any_triangle = true;
    }
  }
  return hit_any_triangle;
}
