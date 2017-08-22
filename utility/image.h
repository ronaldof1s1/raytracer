#ifndef IMAGE_H_
#define IMAGE_H_
	
class image{
	int width, height;
	char * pixels;
public:
	image(int w, int h){
		width = w;
		height = h;
		char buffer[w*h*3];
		pixels = buffer;
	}

	int get_width(){return width;}
	int get_height(){return height;}

	char* get_image_pixels(return pixels;)
}

#endif