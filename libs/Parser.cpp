#include "Parser.h"

std::ifstream input_file;

bool string_to_bool(std::string word, bool &result){
  if(word == "true"){
    result = true;
    return true;
  }
  else if(word == "false"){
    result = false;
    return true;
  }
  else{
    return false;
  }
}

void delete_comments(std::string &str){
  std::size_t pos = str.find('#');
  str = str.substr(0,pos);
}

void split_string(std::string &str, std::string &delim, std::vector< std::string > &words){
  std::string buff = "";
  for(int i = 0; i < str.length(); i++){
    std::string s = std::to_string(str[i]);
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

bool parse_type(std::vector< std::string > &words, int &type){
  if(words.size() == 3){
    if(words[1] == "="){
      if(words[2] == "ppm"){
        type = 3;
        return true;
      }
    }
  }
  return false;
}

bool parse_codification(std::vector< std::string > &words, int &type){
  if(words.size() == 3){
    if(words[1] == "="){
      if(words[2] == "ascii"){
        return true;
      }
      else if(words[2] == "binary"){
        type += 3;
        return true;
      }
    }
  }
  return false;
}

bool parse_width(std::vector< std::string > &words, int &width){
  if(words.size() == 3){
    if(words[1] == "="){
      width = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

bool parse_height(std::vector< std::string > &words, int &height){
  if(words.size() == 3){
    if(words[1] == "="){
      height = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

bool parse_max_color(std::vector< std::string > &words, int &max_color){
  if(words.size() == 3){
    if(words[1] == "="){
      max_color = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

bool parse_antialiasing(std::vector< std::string > &words, int &antialiasing){
  if(words.size() == 3){
    if(words[1] == "="){
      antialiasing = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

bool parse_material(Material *material, int &line_number){
  RGB ambient, diffuse, specular;
  bool has_ambient, has_diffuse, has_specular;
  bool is_lambertian, is_shiny;
  int specular_exponent = 0;

  has_ambient = has_diffuse = has_specular = false;
  is_lambertian = is_shiny = false;

  std::string line = "";

  while (std::getline(input_file, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words[1] == "="){
        if(words[0] == "material"){
          if(words[2] == "lambertian"){
            is_lambertian = true;
          }
          else if(words[2] == "shiny"){
            is_shiny = true;
          }
          else{
            return false;
          }
        }
        else if(words[0] == "ambient"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            ambient = RGB(r,g,b);
            has_ambient = true;
          }
          else{
            return false;
          }
        }
        else if(words[0] == "diffuse"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            diffuse = RGB(r,g,b);
            has_diffuse = true;
          }
          else{
            return false;
          }
        }
        else if(words[0] == "specular"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            specular = RGB(r,g,b);
            has_specular = true;
          }
          else{
            return false;
          }
        }
        else if(words[0] == "specular_exponent"){
          if(words.size() == 3){
            specular_exponent = std::stoi(words[2]);
          }
          else{
            return false;
          }
        }
        else if(words[0] == "END"){
          if(is_lambertian){
            if(has_diffuse){
              if(has_ambient){
                material = new Lambertian(diffuse, ambient);
              }
              else{
                material = new Lambertian(diffuse);
              }
            }
            material = new Lambertian();
          }
          else if(is_shiny){
            if (has_ambient and has_diffuse and has_specular) {
              material = new Shiny(ambient, diffuse, specular, specular_exponent);
            }
          }
          else{
            material = new Material(ambient, diffuse, specular, specular_exponent);
          }
          return (words[1] == "MATERIAL") ? true : false;
        }
        else{
          return false;
        }
      }
      else{
        return false;
      }
    }
  }
}

bool parse_object(Hitable *hitable, int &line_number){
  Point3 center;
  Material *material;
  double radius;

  bool has_center = false;
  bool has_radius = false;
  bool has_material = false;

  bool is_sphere = false;

  std::string line;

  while (std::getline(input_file, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words[0] == "object"){
        if(words.size() == 3 and words[1] == "="){
          if(words[2] == "sphere"){
            is_sphere = true;
          }
          else{
            return false;
          }
        }
      }

      else if(words[0] == "center"){
        if(words.size() == 5 and words[1] == "="){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          center = Point3(x,y,z);
          has_center = true;
        }
      }
      else if(words[0] == "radius"){
        if(words.size() == 3 and words[1] == "="){
          radius = std::stod(words[2]);
          has_radius = true;
        }
      }
      else if(words[0] == "BEGIN"){
        if(words.size() == 2){
          if(words[1] == "MATERIAL"){
            if(!parse_material(material, line_number)){
              return false;
            }
            has_material = true;
          }
          return false;
        }
      }
      else if(words[0] == "END"){
        if(words.size() == 2){
          if(!has_center or !has_material){
            return false;
          }
          if(is_sphere){
            if(!has_radius){
              return false;
            }
            hitable = new Sphere(center, radius, material);
            return (words[1] == "OBJECT") ? true : false;
          }
        }
      }
      else{
        return false;
      }
    }
  }

}

bool parse_background(Background &background, int &line_number){

  bool has_upper_left, has_lower_left;
  bool has_upper_right, has_lower_right;

  has_upper_left = has_upper_right = has_lower_right = has_lower_left = false;

  std::string line;

  while (std::getline(input_file, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.size() == 5 && words[1] == "="){
        if(words[0] == "lower_left"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.lower_left = RGB(r,g,b);
          has_lower_left = true;
        }
        else if(words[0] == "upper_left"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.upper_left = Point3(r,g,b);
          has_upper_left = true;
        }
        else if(words[0] == "upper_right"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.upper_right = Vector3(r,g,b);
          has_upper_right = true;
        }
        else if(words[0] == "lower_right"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.lower_right = Vector3(r,g,b);
          has_lower_right = true;
        }
        else if(words[0] == "END"){
          if(has_lower_left && has_lower_right && has_upper_right && has_upper_left){
            return (words[2] == "BACKGROUND") ? true : false;
          }
          return false;
        }
        else{
          return false;
        }
      }
      return false;
    }
  }
}

bool parse_scene(Scene &scene, int &line_number){}

bool parse_camera(Camera &camera, int &line_number){
  Point3 origin, lower_left_corner;
  Vector3 vertical_axis, horizontal_axis;

  bool has_origin, has_lower_left_corner;
  bool has_vertical_axis, has_horizontal_axis;

  has_origin = has_vertical_axis = has_horizontal_axis = has_lower_left_corner = false;

  std::string line;

  while (std::getline(input_file, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.size() == 5 && words[1] == "="){
        if(words[0] == "origin"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          origin = Point3(x,y,z);
          has_origin = true;
        }
        else if(words[0] == "lower_left_corner"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          lower_left_corner = Point3(x,y,z);
          has_lower_left_corner = true;
        }
        else if(words[0] == "vertical_axis"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          vertical_axis = Vector3(x,y,z);
          has_vertical_axis = true;
        }
        else if(words[0] == "horizontal_axis"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          horizontal_axis = Vector3(x,y,z);
          has_horizontal_axis = true;
        }
        else if(words[0] == "END"){

          if(has_origin && has_lower_left_corner && has_horizontal_axis && has_vertical_axis){
            camera = Camera(origin, lower_left_corner, horizontal_axis, vertical_axis);
            return (words[2] == "CAMERA") ? true : false;
          }
          return false;
        }
        else{
          return false;
        }
      }
      else{
        return false;
      }
    }
  }
}

bool parse_shader(Shader *shader, int &line_number){
  bool ambient, diffuse, specular;
  bool has_ambient, has_diffuse, has_specular, has_shader;
  bool shadow = true;
  double max_depth, iterations;
  iterations = 1;
  max_depth = 1.0;
  has_shader = has_ambient = has_diffuse = has_specular = false;

  bool is_blinn_phong, is_depth_map, is_normal_to_rgb, is_recursive, is_standard;
  is_blinn_phong = is_depth_map = is_normal_to_rgb = is_recursive = is_standard;

  std::string line;

  while (std::getline(input_file, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words.size() == 3 && words[1] == "="){

        if(words[0] == "ambient"){
            if(!string_to_bool(words[2], ambient)){
            return false;
          }
          has_ambient = true;
        }
        else if(words[0] == "diffuse"){
          if(!string_to_bool(words[2], diffuse)){
            return false;
          }
          has_diffuse = true;
        }
        else if(words[0] == "specular"){
          if(!string_to_bool(words[2], specular)){
            return false;
          }
          has_specular = true;
        }
        else if(words[0] == "shadow"){
            if(!string_to_bool(words[2], shadow)){
            return false;
          }
        }
        else if(words[0] == "iterations"){
          iterations = std::stoi(words[2]);
        }
        else if(words[0] == "max_depth"){
          max_depth = std::stod(words[2]);
        }
        else if(words[0] == "shader"){

          if(is_recursive or is_standard or is_depth_map or is_blinn_phong or is_normal_to_rgb){
            return false;
          }
          if(words[2] == "recursive"){
            is_recursive = true;
          }
          else if(words[0] == "diffuse"){
            is_normal_to_rgb = true;
          }
          else if(words[0] == "diffuse"){
            is_depth_map = true;
          }
          else if(words[0] == "diffuse"){
            is_standard = true;
          }
          else if(words[0] == "diffuse"){
            is_blinn_phong = true;
          }
          else{
            return false;
          }

          has_shader = true;
        }
        else if(words[0] == "END"){
          if (has_shader){
            if(is_standard){
              shader = new Standard_shader();
            }
            if(is_normal_to_rgb){
              shader = new Normal_to_RGB();
            }
            if(is_depth_map){
              shader = new Depth_map();
            }
            if(is_recursive){
              if(has_ambient and has_diffuse){
                shader = new Recursive(iterations, ambient, diffuse);
              }
              else{
                shader = new Recursive(iterations);
              }
            }
            if(is_blinn_phong){
              if(has_ambient and has_diffuse and has_specular){
                shader = new Blinn_Phong(ambient, diffuse, specular, shadow);
              }
              else{
                shader = new Blinn_Phong();
              }
            }

            return (words[2] == "SHADER") ? true : false;
          }
          else{
            return false;
          }
        }
        else{
          return false;
        }
      }
    }
  }
}

bool parse_file_name(Image &image, std::string output_file_name){}

bool parse_image(Image &image, Shader *shader, int &line_number){

  int type, max_color, width, height, antialiasing;
  type = max_color = width = height = 0;
  antialiasing = 1;

  bool has_type, has_max_color, has_width, has_height, has_codification;
  has_type = has_max_color = has_width = has_height = has_codification = false;

  Scene scene;
  Camera camera;

  std::string line;

  while (std::getline(input_file, line)) {

    line_number++;

    delete_comments(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words[0] == "type"){
        if(!parse_type(words, type)){
          return false;
        }
        has_type = true;
      }
      else if(words[0] == "codification"){
        if(!parse_codification(words, type)){
          return false;
        }
        has_codification = true;
      }
      else if(words[0] == "width"){
        if(!parse_width(words, width)){
          return false;
        }
        has_width = true;
      }
      else if(words[0] == "height"){
        if (!parse_height(words, height)) {
          return false;
        }
        has_height = true;
      }
      else if(words[0] == "maxcolor"){
        if(!parse_max_color(words, max_color)){
          return false;
        }
        has_max_color = true;
      }
      else if(words[0] == "antialiasing"){
          if(!parse_antialiasing(words, antialiasing)){
            return false;
          }
      }
      else if(words[0] == "BEGIN"){
        if(words[1] == "SCENE"){
          if(!parse_scene(scene, line_number)){
            return false;
          }
        }
        else if(words[1] == "SHADER"){
          if(!parse_shader(shader, line_number)){
            return false;
          }
        }
        else if(words[1] == "CAMERA"){
          if(!parse_camera(camera, line_number)){
            return false;
          }
        }
      }
      else if(words[0] == "END"){
        if(has_type && has_width && has_height && has_max_color){
          image = Image(type, max_color, width, height, scene, camera, antialiasing);
          std::string name;
          if(!parse_file_name(image, name)){
            return false;
          }
          image.name = name;
          return (words[1] == "IMAGE") ? true : false;
        }
        else{
          return false;
        }
      }
      else{
        return false;
      }
    }
  }
}

bool Parser::parse(Image &image, Shader *shader){
  std::ifstream input_file(input_stream, std::ios::in);

  if (input_file.is_open()) {

    std::string line = "";
    int line_number = 0;

    while (std::getline(input_file, line)) {

      line_number++;

      delete_comments(line);

      if(!line.empty()){

        std::vector< std::string > words;

        std::string delim = " ";

        split_string(line, delim, words);

        //first non empty line must be BEGIN IMAGE
        if(words[0] == "BEGIN" && words[1] == "IMAGE"){

          if(parse_image(image, shader, line_number)){
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
