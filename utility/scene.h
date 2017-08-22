#ifndef SCENE_H_
#define SCENE_H_
include "hitable.h"
include <list>

class scene{
	// fields
	std::list< hitable > objects;

	// TODO: constructors & gettes & methods
	scene(std::list< hitable > obj){
		objects = obj;
	}

	std::list< hitable > get_all_objects() {return objects}
	hitable get_object(int i) {
		std::list< hitable >::iterator it = objects.begin();
		while(i-- > 0 && it !=objects.end()){
			it.next();
		}
		return *it;	
	}
	void add_object(hitable object) {objects.push_back(object)}
 };

#endif