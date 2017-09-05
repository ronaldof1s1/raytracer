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

struct Light{
	Point3 source;
	RGB intensity;
};

class Scene{
public:

	// fields
	std::list< Hitable* > objects;
	Background background;
	std::list< Light > lights;
	RGB ambient_light;
	//constructors
	Scene(RGB al = RGB(1,1,1)){
		objects = std::list< Hitable* >();

		background.upper_left = Point3(1.0,1.0,1.0);
		background.lower_left = Point3(1.0,1.0,1.0);
		background.upper_right = Point3(1.0,1.0,1.0);
		background.lower_right = Point3(1.0,1.0,1.0);

		Light light;
		light.source = Point3(-1,1,1);
		light.intensity = RGB(1,1,1);

		lights.push_back(light);

		ambient_light = al;
	};
	Scene(std::list< Hitable* > & obj, RGB al = RGB(1,1,1)){
		objects = obj;

		background.upper_left = Point3(1.0,1.0,1.0);
		background.lower_left = Point3(1.0,1.0,1.0);
		background.upper_right = Point3(1.0,1.0,1.0);
		background.lower_right = Point3(1.0,1.0,1.0);

		Light light;
		light.source = Point3(-1,1,1);
		light.intensity = RGB(1,1,1);

		lights.push_back(light);

		ambient_light = al;
	};

	Scene(Background & bg, RGB al = RGB(1,1,1)){

		objects = std::list< Hitable* >();

		background = bg;

		Light light;
		light.source = Point3(-1,1,1);
		light.intensity = RGB(1,1,1);
		lights.push_back(light);

		ambient_light = al;
	}

	Scene(std::list< Hitable* > & objs, Background & bg, RGB al = RGB(1,1,1)){
		objects = objs;

		background = bg;

		Light light;
		light.source = Point3(-1,1,1);
		light.intensity = RGB(1,1,1);

		lights.push_back(light);

		ambient_light = al;
	}

	Scene(std::list< Hitable* > & objs, Background & bg, std::list< Light > &lights_, RGB al = RGB(1,1,1)){
		objects = objs;

		background = bg;

		lights = lights_;

		ambient_light = al;
	}

	//Methods
	unsigned int size() const {return objects.size();}

	std::list< Hitable* > get_objects() const {return objects;}

	Background get_background() const {return background;}

	RGB get_ambient_light() const {return ambient_light;}

	std::list<Light> get_lights() const { return lights; }

	void add_object(Hitable * object);

	bool hit_anything(const Ray & r, float t_min, float t_max, hit_record & rec) const;
 };


#include "Scene.cpp"
#endif
