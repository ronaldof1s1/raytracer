#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void del_comments(std::string& str){
  size_t pos = str.find("#");
  std::string aux = str.substr(0,pos);
  str = aux;
}

std::vector<std::string> split_string(std::string str, std::string delimiter) {
  std::vector<std::string> *splitted = new std::vector<std::string>();
  int i = 0;
  size_t pos = str.find(delimiter);
  while (pos != std::string::npos) {
    splitted->push_back(str.substr(i,pos-i));
    i = ++pos;
    pos = str.find(delimiter, pos);
    if (pos == std::string::npos) {
      splitted->push_back(str.substr(i,str.length()));
    }
  }
  return *splitted;
}

std::string parse_file_name(std::string line) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  std::string file_name = "";
  if (strs[0].compare("NAME") + strs[1].compare("=") == 0) {
    for (size_t i = 2; i < strs.size(); i++) {
      file_name += strs[i];
      if (i != strs.size() -1) {
        file_name += " ";
      }
    }
  }
  std::cout << file_name << '\n';
  return file_name;
}

int image_type(std::string line) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int file_type = 0;
  if(strs[0].compare("TYPE") + strs[1].compare("=") == 0) {
    if(strs[2].compare("PPM") == 0){
      file_type = 3;
    }
  }
  return file_type;
}

int ascii_or_bin(std::string line, std::string& str, int type) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int file_type = 0;
  if (strs[0].compare("CODIFICATION") + strs[1].compare("=") == 0) {
    if (strs[2].compare("ascii") == 0) {
      file_type = 1;
      str += "P" + std::to_string(type * file_type) + "\n";

    }
    else if(strs[2].compare("binary")== 0){
      file_type = 2;
      str += "P" + std::to_string(type * file_type) + "\n";
    }
  }
  return file_type;
}

int number_of_col(std::string line, std::string &str) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int n_col = -1;
  if (strs[0].compare("WIDTH") + strs[1].compare("=") == 0) {
    str += strs[2] + " ";
    n_col = std::stoi(strs[2]);
  }
  return n_col;
}


int number_of_rows(std::string line, std::string &str) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int n_row = -1;
  if (strs[0].compare("HEIGHT") + strs[1].compare("=") == 0) {
    str += strs[2] + "\n";
    n_row = std::stoi(strs[2]);
  }
  return n_row;
}

std::vector<int>* get_point_rgb(std::string line, std::string point){
  std::cout << line<<std::endl;
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  std::vector<int> *rgb = new std::vector<int>();
  if (strs[0].compare(point) + strs[1].compare("=") == 0) {
    rgb->push_back(std::stoi(strs[2]));
    rgb->push_back(std::stoi(strs[3]));
    rgb->push_back(std::stoi(strs[4]));
  }
  return rgb;
}

void calc_rgb(int i, int j, int n_row, int n_col, std::vector< std::vector<int>* >& four_points, int rgb[] ) {
  int rgb1[3], rgb2[3];
  int r[4];
  int g[4];
  int b[4];
  float x = float(j)/float(n_col);
  float y = float(i)/float(n_row);

  //calc r
  r[0] = four_points.at(0)->at(0); //ul
  r[1] = four_points.at(1)->at(0); //ll
  r[2] = four_points.at(2)->at(0); //ur
  r[3] = four_points.at(3)->at(0); //lr
  rgb1[0] = (r[2] - r[0]) * x + r[0];
  rgb2[0] = (r[3] - r[1]) * x + r[1];


  //calc G
  g[0] = four_points.at(0)->at(1); //ul
  g[1] = four_points.at(1)->at(1); //ll
  g[2] = four_points.at(2)->at(1); //ur
  g[3] = four_points.at(3)->at(1); //lr
  rgb1[1] = (g[2] - g[0]) * x + g[0];
  rgb2[1] = (g[3] - g[1]) * x + g[1];


  //calc b
  b[0] = four_points.at(0)->at(2); //ul
  b[1] = four_points.at(1)->at(2); //ll
  b[2] = four_points.at(2)->at(2); //ur
  b[3] = four_points.at(3)->at(2); //lr
  rgb1[2] = (b[2] - b[0]) * x + b[0];
  rgb2[2] = (b[3] - b[1]) * x + b[1];

  //calc final rgb
  rgb[0] = (rgb2[0] - rgb1[0]) * y + rgb1[0];
  rgb[1] = (rgb2[1] - rgb1[1]) * y + rgb1[1];
  rgb[2] = (rgb2[2] - rgb1[2]) * y + rgb1[2];
  std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;
  //return rgb;
}

std::string generate_ascii_ppm(int n_col, int n_row, std::vector< std::vector<int>* >& four_points) {
  int rgb[3];
  std::string str = "";
  for (size_t i = 0; i < n_row; i++) {
    for (size_t j = 0; j < n_col; j++) {
      calc_rgb(i,j,n_row,n_col,four_points, rgb);
      str += std::to_string(rgb[0]) + " ";
      str += std::to_string(rgb[1]) + " ";
      str += std::to_string(rgb[2]) + "\n";
    }
  }
  //std::cout << str;
  return str;
}

void generate_binary_ppm(int n_col, int n_row, std::vector< std::vector<int>* >& four_points, char buffer[]) {

  int *rgb;
  std::string str = "";
  int count=0;
  for (size_t i = 0; i < n_row; i++) {
    for (size_t j = 0; j < n_col; j++) {
      calc_rgb(i,j,n_row,n_col,four_points,rgb);
      buffer[count++]= rgb[0];
      buffer[count++]= rgb[1];
      buffer[count++]= rgb[2];
    }
  }
}

void generate_image(std::ofstream& out_file, int type, int n_col, int n_row, std::vector< std::vector<int>* > &four_points) {

  if(type == 3) {
    std::string ascii_rgb = generate_ascii_ppm(n_col, n_row, four_points);
    out_file << ascii_rgb;
  }
  if(type == 6) {

    char buffer[n_col * n_row * 3];

    generate_binary_ppm(n_col, n_row, four_points, buffer);
    out_file.write(buffer, n_col*n_row*3);
  }
}

int main(int argc, char const *argv[]) {
  std::string input_file_name = argv[0];
  // std::ifstream input_file(input_file_name, std::ios::in);
  std::ifstream input_file("input_file.txt", std::ios::in);
  std::string output_file_name, file_string = "";
  int image_type_number, n_col, n_row;
  std::vector<int> *upper_left, *upper_right, *lower_left, *lower_right;
  std::vector< std::vector<int>* >* four_points = new std::vector< std::vector<int>* >();
  if (input_file.is_open()) {
    std::string line;
    //getting file name
    std::getline(input_file, line);
    output_file_name = parse_file_name(line);

    //getting file tipe
    std::getline(input_file, line);

    image_type_number = image_type(line);

    //ascii or binary?
    std::getline(input_file, line);
    image_type_number *= ascii_or_bin(line, file_string, image_type_number);

    //getting number of collumns
    std::getline(input_file,line);
    n_col = number_of_col(line, file_string);

    //getting number of rows
    std::getline(input_file,line);

    n_row = number_of_rows(line, file_string);

    //maxcolor = 255
    file_string += "255\n";


    //getting four point rgb
    std::getline(input_file,line);upper_left = get_point_rgb(line, "UPPER_LEFT");
    std::getline(input_file,line);lower_left = get_point_rgb(line, "LOWER_LEFT");
    std::getline(input_file,line);upper_right = get_point_rgb(line, "UPPER_RIGHT");
    std::getline(input_file,line);lower_right = get_point_rgb(line, "LOWER_RIGHT");

    four_points->push_back(upper_left);
    four_points->push_back(lower_left);
    four_points->push_back(upper_right);
    four_points->push_back(lower_right);

    //open out file
    std::ofstream output_file(output_file_name, std::ios::out);
    if (output_file.is_open()) {

      output_file << file_string;

      generate_image (output_file, image_type_number, n_col, n_row, *four_points);
      output_file.close();
    }

    input_file.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  return 0;
}
