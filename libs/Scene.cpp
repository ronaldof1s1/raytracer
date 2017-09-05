#include "Scene.h"

inline void Scene::add_object(Hitable * object){
	objects.push_back(object);
}

//Check in the list of objects if it hits an object
bool Scene::hit_anything(const Ray & r, float t_min, float t_max, hit_record & rec) const{

	bool hit_anything = false;

	//for each object in the list
	for (auto i = objects.begin(); i != objects.end(); i++ ) {
		Hitable *obj = *i;

		//test if the object were hit
	  if(obj->hit(r, t_min, t_max, rec)){
	    hit_anything = true;
	    t_max = rec.t; //closest point to the ray origin
	  }

	}
	return hit_anything;
}
