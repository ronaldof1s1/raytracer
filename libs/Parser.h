#ifndef PARSER_H_
#define PARSER_H
#include <string>
#include <fstream>
#include "Image.h"

class Parser {
  std::ifstream input_file;
public:
  Parser(){}
  Parser(std::ifstream input){
    input_file = input;
  }

  void parse(Image &image);
  void parse_type();
  void parse_width();
  void parse_height();
  void parse_max_color();
  void parse_background();
  void parse_scene();
  void parse_object();
  void parse_sphere();

};

#include "Parser.cpp"
#endif
