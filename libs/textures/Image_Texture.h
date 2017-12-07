#ifndef IMAGE_TEXTURE_H_
#define IMAGE_TEXTURE_H_

#include "../Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../utility/stb_image.h"

class Image_Texture : public Texture{
public:
  int width, height;
  unsigned char *data;
  std::string path;
  Image_Texture(){}

  Image_Texture(std::string path_) {
    int nn;
    const char* p = path_.c_str();
    data = stbi_load(p, &width, &height, &nn, 0);
    path = path_;
  };


  virtual Vector3 value(double u, double v, Point3& p) override;
};

Vector3 Image_Texture::value(double u, double v, Point3& p){
  int i = u*width;
  int j = (1-v) * height -0.001;
  if (i<0) i = 0;
  if (j<0) j = 0;
  if (i > width - 1) i = width-1;
  if (j > height - 1) j = height-1;
  // double r = data[3*i + 3*width*j];
  // double g = data[3*i + 3*width*j+1];
  // double b = data[3*i + 3*width*j+2];
  double r = int(data[3*i + 3*width*j]) / 255.0;
  double g = int(data[3*i + 3*width*j+1]) / 255.0;
  double b = int(data[3*i + 3*width*j+2]) / 255.0;
  RGB rgb(r,g,b);
  // std::cout << "rgb" << rgb << '\n';
  return rgb;
}

#endif
