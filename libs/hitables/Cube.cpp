#include "Cube.h"

void Cube::set_transformation_matrix(Matrix t){
  for(int i = 0; i < triangles.size(); i ++){
		triangles[i].set_transformation_matrix(t);
  }
}


bool Cube::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {
  for(auto triangle : triangles){
    if(!triangle.hit(ray, t_min, t_max, hit_record)){
      return false;
    }
  }
  return true;
}
