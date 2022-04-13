#pragma once

#include <string>

using std::string;

// Комментарии расположены как угодно
// стоит их выровнять или сделать у всех
// один пробел перед ними.
// Также лучше было бы LexemeType,
// TypeLexeme звучит как лексема типа,
// а LexemeType уже правильно: тип лексемы.
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
  // Все эти методы должны быть сделаны статическими!
  bool isInt(const string &lexeme);
  bool isFloat(const string &lexeme);
  bool isVariable(const string &lexeme);
  TypeLexeme typeDefinition(const string &lexeme);
};