#include "scene.h"

inline void scene::add_object(hitable * object){
	objects.push_back(object);
}

bool scene::hit_anything(const Ray & r, float t_min, float t_max, hit_record & rec) {

	bool hit_anything = false;
	for (auto i = objects.begin(); i != objects.end(); i++ ) {
		hitable *obj = *i;

	  if(obj->hit(r, t_min, t_max, rec)){
	    hit_anything = true;
	    t_max = rec.t;
	  }

	}
	return hit_anything;
}