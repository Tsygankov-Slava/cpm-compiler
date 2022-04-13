#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "../AST/AST.h"

using std::cout;
using std::ofstream;
using std::string;

class FileCpp {
private:
  string path = "";

public:
  explicit FileCpp(const string &path) : path(path) {}
  void createFileCPP(Node *head);
};
