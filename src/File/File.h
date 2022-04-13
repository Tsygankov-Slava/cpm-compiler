#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::string;

class File {
private:
  ifstream file;    // Объект файла
  string path = ""; // Путь к файлу
public:
  string code = ""; // Код файла

public:
  File(const string &path) : path(path){};
  void openAndReadFile();
  string getCode();
};
