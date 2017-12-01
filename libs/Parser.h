#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <fstream>
#include <map>
#include "utility/Matrix.h"
#include "Image.h"
#include "cameras/Parallel_Camera.h"
#include "cameras/Perspective_Camera.h"
#include "materials/Lambertian.h"
#include "materials/Shiny.h"
#include "materials/Metal.h"
#include "materials/Cartoon.h"
#include "materials/Normal_Material.h"
#include "materials/Dieletric.h"
#include "shaders/Blinn_Phong.h"
#include "shaders/Depth_map.h"
#include "shaders/Normal_to_RGB.h"
#include "shaders/Recursive.h"
#include "shaders/Standard_shader.h"
#include "shaders/Cel.h"
#include "lights/Directional_light.h"
#include "lights/Pointlight.h"
#include "lights/Spotlight.h"
#include "hitables/Sphere.h"
#include "hitables/Triangle.h"
#include "hitables/Plane.h"
#include "hitables/Cube.h"

class Parser {
  std::string input_stream;
public:
  explicit Parser(std::string input_name){
    input_stream = input_name;
  }

  bool parse(Image &image, Shader *&shader);

};

#include "Parser.cpp"
#endif
