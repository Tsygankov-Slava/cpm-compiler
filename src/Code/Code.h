#pragma once

#include <vector>

#include "../File/File.h"
#include "../Lexer/Lexer.h"

using std::cout;
using std::vector;

class Code : public File, Lexeme {
private:
  string code;
  vector<Lexeme> tokens;

public:
  Code(const string &path, const string &code) : File(path) {
    this->code = code;
  };
  vector<Lexeme> getTokens();
  void printTokens();
};
