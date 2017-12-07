#include "Parser.h"

bool is_blinn_phong, is_depth_map, is_normal_to_rgb, is_recursive, is_standard, is_cel;
bool shadow;
int iterations;
std::map<std::string, Material*> materials;
std::map<std::string, Texture*> textures;

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

bool parse_texture(std::ifstream &input_file, int &line_number){
  Texture *texture;
  RGB color(0);
  Texture *t1, *t2;
  t1 = new Constant_Texture(color);
  t2 = new Constant_Texture(color);
  double scale = 1;
  std::string image_path = "";

  bool is_constant, is_checker, is_noise, is_image;
  is_constant = is_checker = is_noise = is_image = false;

  std::string id = "";
  bool has_id = false;

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

        if(words[0] == "type"){
          if(is_constant or is_checker or is_noise or is_image){
            return false;
          }

          if(words[2] == "constant"){
            is_constant = true;
          }
          else if(words[2] == "checker"){
            is_checker = true;
          }
          else if(words[2] == "noise"){
            is_noise = true;
          }
          else if(words[2] == "image"){
            is_image = true;
          }
          else{
            return false;
          }
        }
        else if (words[0] == "ID"){
          id = words[2];
          has_id = true;
        }
        else if(words[0] == "color"){

          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            color = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        else if(words[0] == "odd_texture"){
          auto it = textures.find(words[2]);
          if(it == textures.end()){
            std::cerr << "texture " << words[2] << " not found" << '\n';
            return false;
          }
          t1 = it->second;
        }
        else if(words[0] == "even_texture"){
          auto it = textures.find(words[2]);
          if(it == textures.end()){
            std::cerr << "texture " << words[2] << " not found" << '\n';
            return false;
          }
          t2 = it->second;
        }
        else if(words[0] == "image_path"){
          for (size_t i = 2; i < words.size(); i++) {
            image_path += words[i];
            if(i < words.size()-1) image_path += " ";
          }
        }
        else if(words[0] == "scale"){
          scale = std::stod(words[2]);
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END"){
        if(!has_id){
          std::cerr << "texture without id" << '\n';
          return false;
        }
        if(is_constant){
          texture = new Constant_Texture(color);
        }
        else if(is_checker){
          texture = new Checker_Texture(t1, t2);
        }
        else if (is_noise){
          texture = new Noise_Texture(color, scale);
        }
        else if (is_image){
          texture = new Image_Texture(image_path);
        }
        else{
          return false;
        }
        textures.emplace(id, texture);
        return (words[1] == "TEXTURE") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_material(std::ifstream &input_file, int &line_number){
  Material* material;
  RGB ambient, diffuse, specular;
  RGB shadow_color, outline;
  bool is_lambertian, is_shiny, is_metal, is_normal, is_cartoon, is_dieletric, has_id;
  int specular_exponent = 0;
  double fuzziness = 1.0;
  double refraction_index = 1.0;
  is_dieletric = is_cartoon = is_normal = is_metal = is_lambertian = is_shiny = has_id = false;
  ambient = diffuse = specular = shadow_color = outline = RGB(0);
  std::string id = "";
  Texture *texture = new Constant_Texture(RGB(0));

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
          if(is_lambertian or is_shiny or is_metal or is_normal or is_cartoon or is_dieletric){
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
          else if(words[2] == "dieletric"){
            is_dieletric = true;
          }
          else{
            return false;
          }
        }
        else if (words[0] == "ID"){
          id = words[2];
          has_id = true;
        }
        else if(words[0] == "texture"){
          auto it = textures.find(words[2]);
          if(it == textures.end()){
            std::cerr << "texture not found" << '\n';
            return false;
          }
          texture = it->second;
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
        else if (words[0] == "refraction_index"){
          if (words.size() == 3) {
            refraction_index = std::stod(words[2]);
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
        if(!has_id){
          std::cerr << "material without id" << '\n';
          return false;
        }
        if(is_lambertian){
          material = new Lambertian(ambient, texture);
        }
        else if(is_shiny){
          material = new Shiny(texture, ambient, specular, specular_exponent);
        }
        else if (is_metal){
          material = new Metal(texture, fuzziness);
        }
        else if (is_normal){
          material = new Normal_Material();
        }
        else if (is_cartoon){
          material = new Cartoon(texture, shadow_color, outline);
        }
        else if (is_dieletric){
          material = new Dieletric(refraction_index, texture);
        }
        else{
          return false;
        }
        materials.emplace(id, material);
        return (words[1] == "MATERIAL") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_cube(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  Point3 v1= Point3(0);
  double size = 0;
  Material *material = new Lambertian(new Constant_Texture(RGB(0)));;
  bool has_material = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}

      if(words[0] == "p1"){
        if(words.size() == 5 and words[1] == "="){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          v1 = Point3(x,y,z);
        }
      }
      else if(words[0] == "size"){
        if(words.size() == 3 and words[1] == "="){
          size = std::stod(words[2]);
        }
      }
      else if(words[0] == "material"){
        std::string id = words[2];
        auto it = materials.find(id);
        if(it == materials.end()){
          std::cerr << "material "<< id << " not found" << '\n';
          return false;
        }
        material = it->second;
        has_material = true;
      }
      else if(words[0] == "END"){
        if(words.size() == 2){
          if(!has_material){
            return false;
          }
          hitable = new Cube(v1, size, material);
          return (words[1] == "CUBE") ? true : false;
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

bool parse_plane(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  Point3 origin = Point3(0);
  double width, height;
  width = height = 1;
  bool culling = false;

  Material *material = new Lambertian(new Constant_Texture(RGB(0)));

  bool has_material = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}

      if(words[0] == "origin"){
        if(words.size() == 5 and words[1] == "="){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          origin = Point3(x,y,z);
        }
      }
      else if(words[0] == "width"){
          if(words.size() == 3 and words[1] == "="){
            width = std::stod(words[2]);
        }
      }
      else if(words[0] == "height"){
          if(words.size() == 3 and words[1] == "="){
            height = std::stod(words[2]);
        }
      }
      else if(words[0] == "material" and words[1] == "="){
        std::string id = words[2];
        auto it = materials.find(id);
        if(it == materials.end()){
          std::cerr << "material "<< id << " not found" << '\n';
          return false;
        }
        material = it->second;
        has_material = true;
      }
      else if(words[0] == "culling" and words[1] == "="){
        if(!string_to_bool(words[2], culling)){
          return false;
        }
      }
      else if(words[0] == "END"){
        if(words.size() == 2){
          if(!has_material){
            return false;
          }
          hitable = new Plane(origin, height, width, material, culling);
          return (words[1] == "PLANE") ? true : false;
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

bool parse_sphere(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  Point3 center = Point3(0);

  Material *material = new Lambertian(new Constant_Texture(RGB(0)));


  double radius = 1.0;

  bool has_material = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}

      if(words[0] == "center"){
          if(words.size() == 5 and words[1] == "="){
            double x = std::stod(words[2]);
            double y = std::stod(words[3]);
            double z = std::stod(words[4]);
            center = Point3(x,y,z);
          }
        }
      else if(words[0] == "radius"){
        if(words.size() == 3 and words[1] == "="){
          radius = std::stod(words[2]);
        }
      }
      else if(words[0] == "material"){
        std::string id = words[2];
        auto it = materials.find(id);
        if(it == materials.end()){
          std::cerr << "material "<< id << " not found" << '\n';
          return false;
        }
        material = it->second;
        has_material = true;
      }
      else if(words[0] == "END"){
        if(words.size() == 2){
          if(!has_material){
            return false;
          }
          hitable = new Sphere(center, radius, material);
          return (words[1] == "SPHERE") ? true : false;
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

bool parse_triangle(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  Point3 v1, v2, v3;
  v1 = v2 = v3 = Point3(0);
  bool culling = true;
  Material *material = new Lambertian(new Constant_Texture(RGB(0)));

  bool has_material = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}

      if (words[1] == "=") {
        if(words[0] == "v1"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          v1 = Point3(x,y,z);
        }
        else if(words[0] == "v2"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          v2 = Point3(x,y,z);
        }
        else if(words[0] == "v3"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          v3 = Point3(x,y,z);
        }
        else if(words[0] == "culling"){
          if (!string_to_bool(words[2], culling)){
            return false;
          }
        }
        else if(words[0] == "material"){
          std::string id = words[2];
          auto it = materials.find(id);
          if(it == materials.end()){
            std::cerr << "material "<< id << " not found" << '\n';
            return false;
          }
          material = it->second;
          has_material = true;
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END"){
        if(!has_material){
          return false;
        }
        hitable = new Triangle(v1,v2,v3,material,culling);
        return (words[1] == "TRIANGLE") ? true : false;
      }

    }
  }
  return false;

}

bool parse_transformations(Matrix &matrix, std::ifstream &input_file, int &line_number){
  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}
      if(words[1] == "="){

        if(words[0] == "translate"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          Matrix translate = translation_matrix(x, y, z);
          matrix = translate * matrix;
          // std::cout << "translate matrix\n" << translate << '\n';
        }
        else if(words[0] == "rotate"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          Matrix rotate = rotation_matrix(x, y, z);
          matrix = rotate * matrix;
          // std::cout << "rotate matrix\n" << rotate << '\n';

        }
        else if(words[0] == "scale"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          Matrix scale = scale_matrix(x, y, z);
          matrix = scale * matrix;
          // std::cout << "scale matrix\n" << scale << '\n';

        }
        else{
          return false;
        }

      }
      else if(words[0] == "END"){
        return (words[1] == "TRANSFORMATIONS") ? true : false;
      }
      else {
        return false;
      }
    }
  }
  return false;

}

bool parse_object(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  if(materials.empty()){
    std::cerr << "must declare materials before objects" << '\n';
    return false;
  }

  Matrix transform = identity_matrix();

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}

      if(words[0] == "BEGIN"){
        if(words[1] == "SPHERE"){
          if(!parse_sphere(hitable, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "TRIANGLE"){
          if(!parse_triangle(hitable, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "CUBE"){
          if(!parse_cube(hitable, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "PLANE"){
          if(!parse_plane(hitable, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "TRANSFORMATIONS"){
          if(!parse_transformations(transform, input_file, line_number)){
            return false;
          }
          hitable->set_transformation_matrix(transform);
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END"){
        return (words[1] == "OBJECT") ? true : false;
      }
      else {
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
      if(words.empty()){continue;}

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

bool parse_light(Light *&light, std::ifstream &input_file, int &line_number){
  bool is_directional, is_pointlight, is_spotlight;
  RGB intensity(1);
  Vector3 direction, source;
  double angular_opening = 90;
  is_directional = is_pointlight = is_spotlight = false;
  direction = source = RGB(0);
  double atenuation = 1;
  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}
      if(words.size() == 5){
        if(words[0] == "source"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          source = Point3(x,y,z);
        }
        else if(words[0] == "direction"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          direction = Point3(x,y,z);
        }
        else if(words[0] == "intensity"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          intensity = RGB(r,g,b);
        }
        else {
          return false;
        }
      }
      else if(words[0] == "opening" and words[1] == "="){
        angular_opening = std::stod(words[2]);
      }
      else if(words[0] == "atenuation" and words[1] == "="){
        atenuation = std::stod(words[2]);
      }
      else if(words[0] == "type" and words[1] == "="){
        if(is_pointlight or is_directional or is_spotlight){
          return false;
        }
        if(words[2] == "pointlight"){
          is_pointlight = true;
        }
        else if(words[2] == "directional"){
          is_directional = true;
        }
        else if(words[2] == "spotlight"){
          is_spotlight = true;
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END"){
        if(is_pointlight){
          light = new Pointlight(source, intensity);
        }
        else if(is_directional){
          light = new Directional_light(direction, intensity);
        }
        else if (is_spotlight){
          light = new Spotlight(source, direction, intensity, angular_opening, atenuation);
        }
        else{
          return false;
        }
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
      if(words.empty()){continue;}
      if(words[0] == "BEGIN"){
        if(words[1] == "BACKGROUND"){
          if(!parse_background(scene.background, input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "LIGHT"){
          Light *light;
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

bool parse_camera(Camera *&camera, std::ifstream &input_file, int &line_number){
  Point3 look_from = Point3(0);
  Vector3 look_at, vp_normal, up;
  look_at = vp_normal = Vector3(0);
  up = Vector3(0, 1, 0);

  bool is_perspective = false;
  bool is_parallel = false;

  //parallel arguments
  Point3 left, right, top, bottom;
  left = Point3(-1,0,0);
  right = Point3(1,0,0);
  top = Point3(0,1,0);
  bottom = Point3(0,-1,0);

  //perspective arguments
  double vfov = 90;
  double aspect_ratio = 2;
  double dist_to_focus = 1;
  double focal_opening = 90;


  std::string line;

  while (std::getline(input_file, line, '\n')) {
    // std::cout << "CAMERA\n";
    line_number++;

    clean_up(line);

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      if(words.empty()){continue;}
      if(words.size() == 5 && words[1] == "="){
        if(words[0] == "look_from"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          look_from = Point3(x,y,z);
        }
        else if(words[0] == "look_at"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          look_at = Point3(x,y,z);
        }
        else if(words[0] == "up"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          up = Vector3(x,y,z);
        }
        else if(words[0] == "vp_normal"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          vp_normal = Vector3(x,y,z);
        }
        else if(words[0] == "left"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          left = Vector3(x,y,z);
        }
        else if(words[0] == "right"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          right = Vector3(x,y,z);
        }
        else if(words[0] == "top"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          top = Vector3(x,y,z);
        }
        else if(words[0] == "bottom"){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          bottom = Vector3(x,y,z);
        }
      }
      else if (words.size() == 3 && words[1] == "="){
        if(words[0] == "type"){
          if(is_perspective or is_parallel){
            std::cerr << "redefinition of camera type" << '\n';
            return false;
          }
          if(words[2] == "perspective"){
            is_perspective = true;
          }
          else if (words[2] == "parallel"){
            is_parallel = true;
          }
          else{
            return false;
          }
        }
        else if (words[0] == "vfov"){
          vfov = std::stod(words[2]);
        }
        else if (words[0] == "dist_to_focus"){
          dist_to_focus = std::stod(words[2]);
        }
        else if (words[0] == "aspect_ratio"){
          aspect_ratio = std::stod(words[2]);
        }
        else if (words[0] == "focal_opening"){
          focal_opening = std::stod(words[2]);
        }
      }
      else if(words[0] == "END"){
        if(is_parallel){
          camera = new Parallel_Camera(look_from, look_at, up, left, right, bottom, top, vp_normal);
        }
        else if(is_perspective){
          camera = new Perspective_Camera(look_from, look_at, up, vfov, aspect_ratio, dist_to_focus, focal_opening, vp_normal);
        }
        else{
          return false;
        }
        return (words[1] == "CAMERA") ? true : false;
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
  ambient = diffuse = specular = true;
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
      if(words.empty()){continue;}

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

  Perspective_Camera *p_camera = dynamic_cast<Perspective_Camera*> (image.get_camera());
  Parallel_Camera *o_camera = dynamic_cast<Parallel_Camera*> (image.get_camera());

  if(p_camera != nullptr){
    output_file_name += "{perspective}_";
  }
  if(o_camera != nullptr){
    output_file_name += "{parallel}_";
  }

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
      shader_name += "_shadow";
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
  Camera *camera;

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
      if(words.empty()){continue;}

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
        else if(words[1] == "MATERIAL"){
          if(!parse_material(input_file, line_number)){
            return false;
          }
        }
        else if(words[1] == "TEXTURE"){
          if(!parse_texture(input_file, line_number)){
            return false;
          }
        }
        else{
          return false;
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
        if(words.empty()){continue;}

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
