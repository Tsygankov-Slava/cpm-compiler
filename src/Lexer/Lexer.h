#pragma once

#include <string>

using std::string;

enum class TypeLexeme {
  PLUS, MINUS, EQUALLY, // + - =
  INT, STRING, FLOAT,
  PRINT, INPUT,
  VAR, VAL,       // Variable, Constant
  SEMICOLON, // ;
  L_PARENTHESIS, R_PARENTHESIS, // ( )
  VARIABLE_NAME,
  NONE_TYPE
};

class Lexeme {
public:
  string lexeme;
  TypeLexeme type;

public:
  bool isInt(const string &lexeme);
  bool isFloat(const string &lexeme);
  bool isVariable(const string &lexeme);
  TypeLexeme typeDefinition(const string &lexeme);
};