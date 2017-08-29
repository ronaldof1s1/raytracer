#ifndef SCENE_H_
#define SCENE_H_

#include "Hitable.h"
#include <list>

using namespace utility;

class Scene{
public:

	// fields
	std::list< Hitable* > objects;

	Scene(){};
	Scene(std::list< Hitable* > & obj){
		objects = obj;
	};

	inline unsigned int size(){return objects.size();}
	std::list< Hitable* > get_objects() {return objects;}

	inline void add_object(Hitable * object);

	inline bool hit_anything(const Ray & r, float t_min, float t_max, hit_record & rec);
 };


#include "Scene.inl"
#endif
