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

bool parse_type(std::vector< std::strig > &words, int &type){
  if(words[1] == "="){
    if(words[2] == "ppm"){
      type = 3;
      return true;
    }
  }
  return false;
}

bool parse_codification(std::vector< std::strig > &words, int &type){
  if(words[1] == "="){
    if(words[2] == "ascii"){
      return true;
    }
    else if(words[2] == "binary"){
      type += 3;
      return true;
    }
  }
  return false;
}

bool parse_width(std::vector< std::strig > &words, int &width){
  if(words[1] == "="){
    width = std::stoi(words[2]);
    return true;
  }
  return false;
}

bool parse_height(std::vector< std::strig > &words, int &height){
  if(words[1] == "="){
    height = std::stoi(words[2]);
    return true;
  }
  return false;
}

bool parse_max_color(std::vector< std::strig > &words, int &max_color){
  if(words[1] == "="){
    max_color = std::stoi(words[2]);
    return true;
  }
  return false;
}

bool parse_antialiasing(std::vector< std::strig > &words, int &antialiasing){
  if(words[1] == "="){
    antialiasing = std::stoi(words[2]);
    return true;
  }
  return false;
}

bool parse_object(Image &image, int &line_number){}
bool parse_background(Image &image, int &line_number){}
bool parse_scene(Image &image, int &line_number){}
void parse_file_name(Image &image, std::string output_file_name){}

bool parse_image(Image &image, Shader *shader, int &line_number){

  int type, max_color, width, height, antialiasing;
  type = max_color = width = height = 0;
  antialiasing = 1;

  bool has_type, has_max_color, has_width, has_height, has_codification;
  has_type = has_max_color = has_width = has_height = has_codification = false;

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
          has_type = true;
          break;

        case "codification":
          if(!parse_codification(words, type)){
            return false;
          }
          has_codification = true;
          break;

        case "width":
          if(!parse_width(words, width)){
            return false;
          }
          has_width = true;
          break;

        case "height":
          if (!parse_height(words, height)) {
            return false;
          }
          has_height = true;
          break;

        case "maxcolor":
          if(!parse_max_color(words, max_color)){
            return false;
          }
          has_max_color = true;
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
            if(has_type && has_width && has_height && has_max_color){
              image = Image(type, max_color, width, height, scene, camera, antialiasing);
              std::string name;
              if(!parse_file_name(image, name)){
                return false;
              }
              return (words[1] == "IMAGE") ? true : false;
            }
            else{
              return false;
            }
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
