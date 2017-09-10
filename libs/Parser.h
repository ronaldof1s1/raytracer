#ifndef PARSER_H_
#define PARSER_H
#include <string>
#include <fstream>
#include "Image.h"
#include "shaders/Blinn_Phong.h"
#include "shaders/Depth_map.h"
#include "shaders/Normal_to_RGB.h"
#include "shaders/Recursive.h"
#include "shaders/Standard_shader.h"

class Parser {
  std::ifstream input_file;
public:
  Parser(){}
  Parser(std::ifstream input){
    input_file = input;
  }

  bool parse(Image &image, Shader *shader);

};

#include "Parser.cpp"
#endif
