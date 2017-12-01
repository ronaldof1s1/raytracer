#ifndef CUBE_H_
#define CUBE_H_

#include <vector>
#include "../Hitable.h"
#include "triangle.h"

class Cube : public Hitable {
public:
	std::vector<Triangle> triangles;
	Vector3 normal;
	Box(Point3 e0, Point3 e7, Material *mat)
  {
    Point3 e1(e7.x(), e0.y(), e0.z());
    Point3 e2(e7.x(), e7.y(), e0.z());
    Point3 e3(e0.x(), e7.y(), e0.z());
    Point3 e4(e0.x(), e0.y(), e7.z());
    Point3 e5(e7.x(), e0.y(), e7.z());
    Point3 e6(e0.x(), e7.y(), e7.z());

    triangles.push_back(Triangle(e0, e1, e3, mat, true));
    triangles.push_back(Triangle(e3, e1, e2, mat, true));
    triangles.push_back(Triangle(e1, e7, e2, mat, true));
    triangles.push_back(Triangle(e1, e5, e7, mat, true));
    triangles.push_back(Triangle(e3, e7, e6, mat, true));
    triangles.push_back(Triangle(e3, e2, e7, mat, true));
    triangles.push_back(Triangle(e4, e3, e6, mat, true));
    triangles.push_back(Triangle(e4, e0, e3, mat, true));
    triangles.push_back(Triangle(e7, e4, e6, mat, true));
    triangles.push_back(Triangle(e7, e5, e4, mat, true));
    triangles.push_back(Triangle(e1, e4, e5, mat, true));
    triangles.push_back(Triangle(e1, e0, e4, mat, true));

    material = mat;
  };

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) override ;

  void set_transformation_matrix(Matrix t) override;

};


#endif
