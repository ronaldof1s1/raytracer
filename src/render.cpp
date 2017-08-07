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


int main(int argc, char const *argv[]) {
  std::string input_file_name = argv[0];
  // std::ifstream input_file(input_file_name, std::ios::in);
  std::ifstream input_file("input_file.txt", std::ios::in);
  std::string output_file_name;
  
  if (input_file.is_open()) {
    std::string line;
    //getting file name
    std::getline(input_file, line);
    output_file_name = parse_file_name(line);

    input_file.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  return 0;
}
