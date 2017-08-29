#ifndef SCENE_H_
#define SCENE_H_

#include "hitable.h"
#include <list>

using namespace utility;

class scene{
public:

	// fields
	std::list< hitable* > objects;

	scene(){};
	scene(std::list< hitable* > & obj){
		objects = obj;
	};

	inline unsigned int size(){return objects.size();}
	std::list< hitable* > get_objects() {return objects;}
	
	inline void add_object(hitable * object);

	inline bool hit_anything(const Ray & r, float t_min, float t_max, hit_record & rec);
 };


#include "scene.inl"
#endif