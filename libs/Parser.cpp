#include "Parser.h"
void delete_comments(std::string &str){
  std::size_t pos = str.find('#');
  str = srt.substr(0,pos);
}

void split_string(std::string &str, std::string &delim, std::vector< std::string > &words){
  std::string buff = "";
  for(auto s:str){
    if (s != delim){
      buff += s;
    }
    if(s == delim && buff != ""){
      words.push_back(buff);
      buff = "";
    }
  }
  if (buff != ""){
    words.push_back(buff);
  }
}

bool parse_type(std::vector< std::strig > &words, int &type){}
bool parse_width(){}
bool parse_height(){}
bool parse_max_color(){}
bool parse_background(Image &image, int &line_number){}
bool parse_scene(Image &image, int &line_number){}
bool parse_object(Image &image, int &line_number){}
bool parse_sphere(){}
bool parse_file_name(std::vector< std::strig > &words){}
bool parse_image(Image &image, int &line_number){

  int type, max_color, width, height, antialiasing;
  Scene scene;
  Camera cam;

  while (std::getline(input_stream, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      split_string(line, " ", words);

      switch (words[0]) {
        case "type":
          if(!parse_type(words, type)){
            return false;
          }
          break;

        case "codification":
          if(!parse_codification(words, type)){
            return false;
          }
          break;

        case "width":
          if(!parse_width(words, width)){
            return false;
          }
          break;

        case "height":
          if (!parse_height(words, height)) {
            return false;
          }
          break;

        case "maxcolor":
          if(!parse_max_color(words, max_color)){
            return false;
          }
          break;

        case "antialiasing":
          if(!parse_antialiasing(words, antialiasing)){
            return false;
          }
          break;

        case "BEGIN":
          switch (words[2]) {
            case "SCENE":
              if(!parse_scene(scene, line_number)){
                return false;
              }
              break;

            case "SHADER":
              if(!parse_shader(shader, line_number)){
                return false;
              }
              break;

            case "CAMERA":
              if(!parse_scene(camera, line_number)){
                return false;
              }
              break;
          }
          break;

          case "END":
            //final line must be "END IMAGE"
            return (words[1] == "IMAGE") ? true : false;
            break;


      }
    }
}

bool Parser::parse(Image &image, Shader *shader){

  if (input_stream.is_open()) {

    std::string line;
    int line_number = 0;

    while (std::getline(input_file, line)) {

      line_number++;

      delete_comments(line);

      if(!line.empty()){

        std::vector< std::string > words;

        split_string(line, " ", words);

        //first non empty line must be BEGIN IMAGE
        if(words[0] == "BEGIN" && words[1] == "IMAGE"){

          if(parse_image(input_file, image, line_number)){
            return true;
          }
          else{
            std::cerr << "Error at line: " << line_number << std::endl;
            return false;
          }

        }
      }
    }
    input_file.close();
  }
  else {
    std::cerr << "Unable to open file\n";
    return false;
  }
};
