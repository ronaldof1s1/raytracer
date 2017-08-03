#ifndef __VECTOR_H_
#define __VECTOR_H_

class Vector3{
public:

	//Aliases
	typedef float value_type;
	enum field_t : int {X=0, Y=1, Z=2, R=0, G=1, B=2};

	//Fields
	value_type e[3];
	
};

#endif