#pragma once

#include <string>

#include "../Lexer/Lexer.h"

using std::make_pair;
using std::pair;
using std::string;
using std::swap;

class Mixed {
public:
  Lexeme lexeme;

public:
  Mixed(){};
  Mixed(Lexeme lexeme) : lexeme(lexeme){};
  friend pair<Mixed, Mixed> operator+(Mixed &a, Mixed &b);
  friend pair<Mixed, Mixed> operator-(Mixed &a, Mixed &b);
};
