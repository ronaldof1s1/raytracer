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
	Cube(Point3 p0, double size, Material *mat) {
		edge_size = size;
    Point3 p1(p0.x() + size, p0.y(), p0.z());

    Point3 p2(p0.x(), p0.y() + size, p0.z());

    Point3 p3(p0.x(), p0.y(), p0.z() + size);

    Point3 p4(p0.x() + size, p0.y() + size, p0.z());

    Point3 p5(p0.x() + size, p0.y(), p0.z() + size);

    Point3 p6(p0.x(), p0.y() + size, p0.z() + size);

		Point3 p7(p0.x() + size, p0.y() + size, p0.z() + size);
		Triangle *t;
		//Face back
		t = new Triangle(p4, p1, p2, mat, true);
		triangles.push_back(t);
		t = new Triangle(p1, p0, p2, mat, true);
    triangles.push_back(t);

		//face left
		t = new Triangle(p2, p0, p3, mat, true);
    triangles.push_back(t);
		t = new Triangle(p6, p2, p3, mat, true);
    triangles.push_back(t);

		//face right
		t = new Triangle(p7, p5, p4, mat, true);
    triangles.push_back(t);
		t = new Triangle(p5, p1, p4, mat, true);
		triangles.push_back(t);

		//face front
		t = new Triangle(p3, p5, p7, mat, true);
    triangles.push_back(t);
		t = new Triangle(p3, p7, p6, mat, true);
    triangles.push_back(t);


		//face top
		t = new Triangle(p2, p7, p4, mat, true);
		triangles.push_back(t);
		t= new Triangle(p7, p2, p6, mat, true);
    triangles.push_back(t);

		//face bottom
		t = new Triangle(p5, p0, p1, mat, true);
    triangles.push_back(t);
		t = new Triangle(p3, p0, p5, mat, true);
    triangles.push_back(t);

    material = mat;
  };

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) override ;

  virtual void set_transformation_matrix(Matrix t) override;

};

#include "Cube.cpp"

#endif
