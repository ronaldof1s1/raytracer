#ifndef IMAGE_H_
#define IMAGE_H_
#include <vector>
#include "Scene.h"
#include "Camera.h"


class Image{
	int type;
	int max_color;
	int width, height;
	Scene scene;
	Camera camera;
	
public:
	Image(){}
	Image(int t, int w, int h, Scene &sce, Camera &cam){
		width = w;
		height = h;
		scene = sce;
		camera = cam;
		type = t;
	}

	Image(int t, int color, int w, int h, Scene &sce, Camera &cam){
		width = w;
		height = h;
		scene = sce;
		camera = cam;
		type = t;
		max_color = color;
	}

	int get_width(){return width;}
	int get_height(){return height;}
	int get_type(){return type;}
	int get_max_color(){return max_color;}

	Camera get_camera(){return camera;}
	Scene get_scene(){return scene;}
	Background get_background(){return scene.get_background();}
};

#endif
