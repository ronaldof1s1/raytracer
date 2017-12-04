#ifndef CUBE_H_
#define CUBE_H_

#include <vector>
#include "../Hitable.h"
#include "Triangle.h"

class Cube : public Hitable {
public:
	std::vector<Triangle*> triangles;
	double edge_size;
	
	Cube () {}
	Cube(Point3 e0, double size, Material *mat) {
		edge_size = size;
    Point3 e1(e0.x() + size, e0.y(), e0.z());

    Point3 e2(e0.x(), e0.y() + size, e0.z());

    Point3 e3(e0.x(), e0.y(), e0.z() + size);

    Point3 e4(e0.x() + size, e0.y() + size, e0.z());

    Point3 e5(e0.x() + size, e0.y(), e0.z() + size);

    Point3 e6(e0.x(), e0.y() + size, e0.z() + size);

		Point3 e7(e0.x() + size, e0.y() + size, e0.z() + size);


    triangles.push_back(new Triangle(e0, e1, e2, mat, true));
    triangles.push_back(new Triangle(e1, e2, e4, mat, true));
    triangles.push_back(new Triangle(e0, e2, e3, mat, true));
    triangles.push_back(new Triangle(e2, e3, e6, mat, true));
    triangles.push_back(new Triangle(e1, e5, e4, mat, true));
    triangles.push_back(new Triangle(e5, e7, e4, mat, true));
    triangles.push_back(new Triangle(e3, e5, e7, mat, true));
    triangles.push_back(new Triangle(e5, e7, e6, mat, true));
    triangles.push_back(new Triangle(e2, e4, e7, mat, true));
    triangles.push_back(new Triangle(e4, e7, e6, mat, true));
    triangles.push_back(new Triangle(e0, e1, e5, mat, true));
    triangles.push_back(new Triangle(e1, e5, e3, mat, true));

    material = mat;
  };

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) override ;

  virtual void set_transformation_matrix(Matrix t) override;

};

#include "Cube.cpp"

#endif
