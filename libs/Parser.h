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

  bool parse(Image &image, Shader *shader);

};

#include "Parser.cpp"
#endif
