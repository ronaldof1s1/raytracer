#ifndef SCENE_H_
#define SCENE_H_

#include "Hitable.h"
#include <list>

using namespace utility;

struct Background{
	Point3 upper_left;
	Point3 lower_left;
	Point3 upper_right;
	Point3 lower_right;
};

class Scene{
public:

	// fields
	std::list< Hitable* > objects;
	Background background;

	//constructors
	Scene(){};
	Scene(std::list< Hitable* > & obj){
		objects = obj;
		background.upper_left = Point3(1.0,1.0,1.0);
		background.lower_left = Point3(1.0,1.0,1.0);
		background.upper_right = Point3(1.0,1.0,1.0);
		background.lower_right = Point3(1.0,1.0,1.0);
	};

	Scene(Background & bg){
		background = bg;
	}

	Scene(std::list< Hitable* > & objs, Background & bg){
		objects = objs;
		background = bg;
	}

	//Methods
	unsigned int size(){return objects.size();}

	std::list< Hitable* > get_objects() {return objects;}

	Background get_background() {return background;}

	void add_object(Hitable * object);

	bool hit_anything(const Ray & r, float t_min, float t_max, hit_record & rec);
 };


#include "Scene.cpp"
#endif
