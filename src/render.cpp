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

int image_type(std::string line, std::string& str) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int file_type = 0;
  if (strs[0].compare("CODIFICATION") + strs[1].compare("=") == 0) {
    if (strs[2].compare("ascii")) {
      str += "P3\n";
      file_type = 3;
    }
    else if(strs[2].compare("binary")){
      str += "P6\n";
      file_type = 6;
    }
  }
  return file_type;
}

int number_of_col(std::string line, std::string str) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int n_col = -1;
  if (strs[0].compare("WIDTH") + strs[1].compare("=") == 0) {
    str += strs[2] + " ";
    n_col = std::stoi(strs[2]);
  }
  return n_col;
}


int number_of_rows(std::string line, std::string str) {
  del_comments(line);
  std::vector<std::string> strs = split_string(line, " ");
  int n_row = -1;
  if (strs[0].compare("HEIGHT") + strs[1].compare("=") == 0) {
    str += strs[2] + " ";
    n_row = std::stoi(strs[2]);
  }
  return n_row;
}

std::vector<int>* get_point_rgb(std::string line, std::string point){
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

int main(int argc, char const *argv[]) {
  std::string input_file_name = argv[0];
  // std::ifstream input_file(input_file_name, std::ios::in);
  std::ifstream input_file("input_file.txt", std::ios::in);
  std::string output_file_name, file_string = "";
  int image_type_number, n_col, n_row;
  std::vector<int> *upper_left, *upper_right, *lower_left, *lower_right;
  if (input_file.is_open()) {
    std::string line;
    //getting file name
    std::getline(input_file, line);
    output_file_name = parse_file_name(line);

    //getting file tipe
    std::getline(input_file, line);
    std::getline(input_file, line);
    image_type_number = image_type(line, file_string);

    //getting number of collumns
    std::getline(input_file,line);
    n_col = number_of_col(line, file_string);

    //getting number of rows
    std::getline(input_file,line);
    n_row = number_of_rows(line, file_string);

    //getting four point rgb
    upper_left = get_point_rgb(line, "UPPER_LEFT");
    lower_left = get_point_rgb(line, "LOWER_LEFT");
    upper_right = get_point_rgb(line, "UPPER_RIGHT");
    lower_right = get_point_rgb(line, "LOWER_RIGHT");

    input_file.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  return 0;
}
