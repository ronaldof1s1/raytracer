#include "Parser.h"

bool is_blinn_phong, is_depth_map, is_normal_to_rgb, is_recursive, is_standard, is_cel;
bool shadow;
int iterations;

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

void clean_up(std::string &str){
  // Deletes the comments
  std::size_t pos = str.find('#');

  if(pos != std::string::npos){
    str = str.substr(0,pos);
  }

  if(str.back() == '\r'){
    str.pop_back();
  }
}

void split_string(std::string &str, std::string &delimiter, std::vector< std::string > &words){
  // Splits a string based on a delimiter

  int i = 0;
  size_t pos = str.find(delimiter);
  std::string buff = "";

  while (pos != std::string::npos) {
    buff = str.substr(i,pos-i);

    if(!buff.empty()){
      words.push_back(buff);
    }

    i = ++pos;
    pos = str.find(delimiter, pos);

    if (pos == std::string::npos) {
      buff = str.substr(i,str.length());

      if(!buff.empty()){
        words.push_back(buff);
      }
    }
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

bool parse_material(Material *&material, std::ifstream &input_file, int &line_number){
  RGB ambient, diffuse, specular, albedo;
  RGB shadow_color, outline;
  bool is_lambertian, is_shiny, is_metal, is_normal, is_cartoon;
  int specular_exponent = 0;
  double fuzziness = 1.0;
  is_cartoon = is_normal = is_metal = is_lambertian = is_shiny = false;
  ambient = diffuse = specular = albedo = shadow_color = outline = RGB(0);
  std::string line = "";

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delimiter = " ";

      split_string(line, delimiter, words);

      if(words[1] == "="){

        if(words[0] == "material"){
          if(is_lambertian or is_shiny or is_metal or is_normal or is_cartoon){
            return false;
          }

          if(words[2] == "lambertian"){
            is_lambertian = true;
          }
          else if(words[2] == "shiny"){
            is_shiny = true;
          }
          else if(words[2] == "metal"){
            is_metal = true;
          }
          else if(words[2] == "normal"){
            is_normal = true;
          }
          else if(words[2] == "cartoon"){
            is_cartoon = true;
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
          }
          else{
            return false;
          }
        }
        else if(words[0] == "albedo"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            albedo = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        else if(words[0] == "shadow"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            shadow_color = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        else if(words[0] == "outline"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            outline = RGB(r,g,b);
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
        else if (words[0] == "fuzziness"){
          if (words.size() == 3) {
            fuzziness = std::stod(words[2]);
          }
          else{
            return false;
          }
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END"){
        if(is_lambertian){
          material = new Lambertian(ambient, albedo);
        }
        else if(is_shiny){
          material = new Shiny(ambient, diffuse, specular, specular_exponent);
        }
        else if (is_metal){
          material = new Metal(albedo, fuzziness);
        }
        else if (is_normal){
          material = new Normal_Material();
        }
        else if (is_cartoon){
          material = new Cartoon(albedo, shadow_color, outline);
        }
        else{
          return false;
        }
        return (words[1] == "MATERIAL") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_object(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  Point3 center;
  Material *material;
  double radius = 1.0;

  bool has_center = false;
  bool has_radius = false;
  bool has_material = false;

  bool is_sphere = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

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
            if(!parse_material(material, input_file, line_number)){

              // std::cout << "aqui" << '\n';
              return false;
            }
            has_material = true;
          }
          else{
            return false;
          }
        }
        else{
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
  return false;
}

bool parse_background(Background &background, std::ifstream &input_file, int &line_number){

  bool has_upper_left, has_lower_left;
  bool has_upper_right, has_lower_right;

  has_upper_left = has_upper_right = has_lower_right = has_lower_left = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

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
          // std::cout << "aqui" << '\n';
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
      }
      else if(words[0] == "END"){
        if(has_lower_left && has_lower_right && has_upper_right && has_upper_left){
          return (words[1] == "BACKGROUND") ? true : false;
        }
        return false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_light(Light &light, std::ifstream &input_file, int &line_number){
  RGB intensity(1);
  Point3 source(0);

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.size() == 5){
        if(words[0] == "source"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          source = Point3(x,y,z);
          light.source = source;
        }
        else if(words[0] == "intensity"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          intensity = RGB(r,g,b);
          light.intensity = intensity;
        }
        else {
          return false;
        }
      }
      else if(words[0] == "END"){
        return (words[1] == "LIGHT") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_scene(Scene &scene, std::ifstream &input_file, int &line_number){

  RGB ambient_light(1);
  scene = Scene();

  std::string line;

  // for (int i = 0; i < line_number i++){std::getline(input_file,line,'\n'); clean_up(line)}

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words[0] == "BEGIN"){
        if(words[1] == "BACKGROUND"){
          if(!parse_background(scene.background, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "LIGHT"){
          Light light;
          if(!parse_light(light, input_file, line_number)){
            return false;
          }
          else{
            scene.add_light(light);
          }
        }
        else if(words[1] == "OBJECT"){
          Hitable *object;
          if(!parse_object(object, input_file, line_number)){
            return false;
          }
          else{
            scene.add_object(object);
          }
        }
        else{
          return false;
        }
      }
      else if(words.size() == 5 and words[0] == "ambient_light" and words[1] == "="){
        double r = std::stod(words[2]);
        double g = std::stod(words[3]);
        double b = std::stod(words[4]);
        ambient_light = RGB(r,g,b);
        scene.ambient_light = ambient_light;
      }
      else if(words[0] ==  "END"){
        return (words[1] == "SCENE") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_camera(Camera &camera, std::ifstream &input_file, int &line_number){
  Point3 origin, lower_left_corner;
  Vector3 vertical_axis, horizontal_axis;

  bool has_origin, has_lower_left_corner;
  bool has_vertical_axis, has_horizontal_axis;

  has_origin = has_vertical_axis = has_horizontal_axis = has_lower_left_corner = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {
    // std::cout << "CAMERA\n";
    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

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
      }
      else if(words[0] == "END"){

        if(has_origin && has_lower_left_corner && has_horizontal_axis && has_vertical_axis){
          camera = Camera(origin, lower_left_corner, vertical_axis, horizontal_axis);
          return (words[1] == "CAMERA") ? true : false;
        }
        return false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_shader(Shader *&shader, std::ifstream &input_file, int &line_number){
  bool ambient, diffuse, specular;
  ambient = diffuse = specular = false;
  bool has_shader;
  double max_depth;
  shadow = true;
  iterations = 1;
  max_depth = 1.0;
  has_shader = false;
  std::vector<int> thresholds;
  int outline_threshold = 85;
  is_blinn_phong = is_depth_map = is_normal_to_rgb = is_recursive = is_standard = is_cel = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words.size() == 3 && words[1] == "="){

        if(words[0] == "ambient"){
            if(!string_to_bool(words[2], ambient)){
            return false;
          }
        }
        else if(words[0] == "diffuse"){
          if(!string_to_bool(words[2], diffuse)){
            return false;
          }
        }
        else if(words[0] == "specular"){
          if(!string_to_bool(words[2], specular)){
            return false;
          }
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
        else if(words[0] == "outline_threshold"){
          outline_threshold = std::stoi(words[2]);
        }
        else if (words[0] == "threshold"){
          thresholds.push_back(std::stoi(words[2]));
        }
        else if(words[0] == "shader"){

          if(is_recursive or is_standard or is_depth_map or is_blinn_phong or is_normal_to_rgb or is_cel){
            return false;
          }
          if(words[2] == "recursive"){
            is_recursive = true;
          }
          else if(words[2] == "normal2rgb"){
            is_normal_to_rgb = true;
          }
          else if(words[2] == "depthmap"){
            is_depth_map = true;
          }
          else if(words[2] == "standard"){
            is_standard = true;
          }
          else if(words[2] == "blinnphong"){
            is_blinn_phong = true;
          }
          else if(words[2] == "cel"){
            is_cel = true;
          }
          else{
            return false;
          }

          has_shader = true;
        }
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
            shader = new Depth_map(max_depth);
          }
          if(is_recursive){
            shader = new Recursive(iterations);
          }
          if(is_blinn_phong){
            shader = new Blinn_Phong(ambient, diffuse, specular, shadow);
          }
          if(is_cel){
            shader = new Cel(thresholds, outline_threshold);
          }
          return (words[1] == "SHADER") ? true : false;
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
  return false;
}

void parse_file_name(Image &image, Shader *shader){
  std::string output_file_name = "";
  output_file_name += "{P" + std::to_string(image.get_type())+"}_";
  output_file_name += "{" + std::to_string(image.get_width()) + "x" + std::to_string(image.get_height()) + "}_";
  output_file_name += "{" + std::to_string(image.get_antialiasing()) + "x}_";
  std::string shader_name = "";

  if(is_blinn_phong){
    Blinn_Phong *bp = dynamic_cast<Blinn_Phong*>(shader);

    shader_name += "Blinn_Phong";

    if(bp->use_ambient == 1.0){
      shader_name += "_ambient";
    }
    if(bp->use_diffuse == 1.0){
      shader_name += "_diffuse";
    }
    if(bp->use_specular == 1.0){
      shader_name += "_specular";
    }
    if (shadow) {
      output_file_name += "_shadow";
    }
  }
  else if(is_standard){
    shader_name += "Standard_shader";
  }
  else if(is_depth_map){
    Depth_map *dm = dynamic_cast<Depth_map*>(shader);
    shader_name += "Depth_map_depth_at_" + std::to_string(dm->max_depth);
  }
  else if(is_normal_to_rgb){
    shader_name += "Normal_to_RGB";
  }
  else if(is_recursive){
    shader_name += "Recursive_" + std::to_string(iterations) + "_iterations";
  }
  else if(is_cel){
    Cel *cel = dynamic_cast<Cel*>(shader);
    shader_name += "Cel_outline_at_" + std::to_string(cel->outline_threshold);
  }

  output_file_name += "{" + shader_name + "}_";

  image.set_file_name(output_file_name);

}

bool parse_image(Image &image, Shader *&shader, std::ifstream &input_file, int &line_number){

  int type, max_color, width, height, antialiasing;
  type = max_color = width = height = 0;
  antialiasing = 1;

  bool has_type, has_max_color, has_width, has_height, has_codification;
  has_type = has_max_color = has_width = has_height = has_codification = false;

  Scene scene;
  Camera camera;

  std::string line;

  while (std::getline(input_file, line, '\n')) {
    // std::cout << "parse_image" << std::endl;
    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

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
          if(!parse_scene(scene, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "SHADER"){
          if(!parse_shader(shader, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "CAMERA"){
          if(!parse_camera(camera, input_file, line_number)){
            return false;
          }
        }
      }
      else if(words[0] == "END"){
        if(has_type && has_width && has_height && has_max_color){
          image = Image(type, max_color, width, height, scene, camera, antialiasing);
          parse_file_name(image, shader);
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
  return false;
}

bool Parser::parse(Image &image, Shader *&shader){
  std::ifstream input_file(input_stream, std::ios::in);

  if (input_file.is_open()) {

    std::string line = "";
    int line_number = 0;

    while (std::getline(input_file, line, '\n')) {
      line_number++;

      clean_up(line);
      // std::cout << line <<std::endl;

      if(!line.empty()){

        std::vector< std::string > words;

        std::string delim = " ";

        split_string(line, delim, words);

        //first non empty line must be BEGIN IMAGE
        if(words[0] == "BEGIN" and words[1] == "IMAGE"){
          // std::cout << line << std::endl;
          if(parse_image(image, shader, input_file, line_number)){
            return true;
            if (shader == nullptr) {
              std::cout << "nullptr parse" << '\n';
            }
          }
          else{
            std::cerr << "Error at line: " << line_number << std::endl;
            return false;
          }

        }
        else{
          std::cerr << "Error at line: " << line_number << std::endl;
          return false;
        }
      }
    }
    return false;
    input_file.close();
  }
  else {
    std::cerr << "Unable to open file\n";
    return false;
  }
};
